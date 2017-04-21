#include <QtCore/QSettings>
#include <QtCore/QUuid>
#include <QtCore/QDebug>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setDockNestingEnabled(true);
    setCentralWidget(Q_NULLPTR);

    loadHostEntries();
}

/**
 * Loads all host entries
 */
void MainWindow::loadHostEntries() const {
    const QSignalBlocker blocker(ui->entryTreeWidget);
    Q_UNUSED(blocker);

    QSettings settings;
    QStringList hostEntryKeys = settings.value("HostEntryKeys").toStringList();
    ui->entryTreeWidget->clear();
    Q_FOREACH(QString key, hostEntryKeys) {
            QString name = settings.value(hostEntrySettingsKey(key, "Name"),
                                          tr("New entry")).toString();
            bool enabled = settings.value(
                    hostEntrySettingsKey(key, "Enabled")).toBool();

            createHostEntryTreeWidgetItem(key, name, enabled);
        }
}

const QString MainWindow::hostEntrySettingsKey(
        const QString &key, QString variableName) const {
    return "HostEntry-" + key + "/" + variableName;
}

/**
 * Creates a host entry tree widget item
 *
 * @param key
 * @param name
 * @return
 */
QTreeWidgetItem *MainWindow::createHostEntryTreeWidgetItem(const QString &key,
                                                           const QString &name,
                                                           bool enabled) const {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setData(0, Qt::UserRole, key);
    item->setText(0, name);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable |
                   Qt::ItemIsEditable);
    item->setCheckState(0, enabled ? Qt::Checked : Qt::Unchecked);
    ui->entryTreeWidget->addTopLevelItem(item);
    return item;
}

MainWindow::~MainWindow() {
    delete ui;
}

/**
 * Adds a new host entry
 */
void MainWindow::on_actionNew_entry_triggered() {
    QSettings settings;

    QStringList hostEntryKeys = settings.value("HostEntryKeys").toStringList();
    QString key = generateUuid();
    QString name = tr("New entry");

    hostEntryKeys.append(key);
    settings.setValue("HostEntryKeys", hostEntryKeys);
    settings.setValue(hostEntrySettingsKey(key, "Name"), name);
    settings.setValue(hostEntrySettingsKey(key, "Enabled"), true);

    createHostEntryTreeWidgetItem(key, name, true);
}

/**
 * Generates an uuid
 *
 * @return
 */
QString MainWindow::generateUuid() const {
    QString uuid = QUuid::createUuid().toString();
    uuid.replace("{", "").replace("}", "");
    return uuid;
}

/**
 * Quits the application
 */
void MainWindow::on_actionQuit_triggered() {
    QApplication::quit();
}

/**
 * Sets the new name and enabled state for a host entry
 *
 * @param item
 * @param column
 */
void MainWindow::on_entryTreeWidget_itemChanged(QTreeWidgetItem *item,
                                                int column) {
    Q_UNUSED(column);
    QSettings settings;
    QString key = item->data(0, Qt::UserRole).toString();
    settings.setValue(hostEntrySettingsKey(key, "Name"), item->text(0));
    settings.setValue(hostEntrySettingsKey(key, "Enabled"),
                      item->checkState(0) == Qt::Checked);
}

/**
 * Loads the host entry data
 *
 * @param current
 * @param previous
 */
void MainWindow::on_entryTreeWidget_currentItemChanged(
        QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    QSettings settings;
    QString key = current->data(0, Qt::UserRole).toString();
    QString data = settings.value(hostEntrySettingsKey(key, "Data")).toString();
    const QSignalBlocker blocker(ui->entryTextEdit);
    Q_UNUSED(blocker);
    ui->entryTextEdit->setText(data);
}

/**
 * Stores host data to a host entry
 */
void MainWindow::on_entryTextEdit_textChanged() {
    QTreeWidgetItem *item = ui->entryTreeWidget->currentItem();

    if (item == Q_NULLPTR) {
        return;
    }
    QSettings settings;
    QString key = item->data(0, Qt::UserRole).toString();
    settings.setValue(hostEntrySettingsKey(key, "Data"),
                      ui->entryTextEdit->toPlainText());

}

void MainWindow::on_entryTreeWidget_customContextMenuRequested(
        const QPoint &pos) {
    QPoint globalPos = ui->entryTreeWidget->mapToGlobal(pos);
    QMenu *menu = new QMenu();

    QAction *removeEntryAction = menu->addAction("Remove");
    removeEntryAction->setShortcut(
            ui->actionRemove_selected_host_entries->shortcut());

    QAction *selectedItem = menu->exec(globalPos);
    if (selectedItem) {
        if (selectedItem == removeEntryAction) {
            removeSelectedHostEntries();
        }
    }

}

/**
 * Removes all selected host entries
 */
void MainWindow::removeSelectedHostEntries() {
    QList <QTreeWidgetItem *> itemList = ui->entryTreeWidget->selectedItems();
    int selectedItemsCount = itemList.count();

    if (selectedItemsCount == 0) {
        return;;
    }
    
    if (QMessageBox::information(
            this,
            tr("Remove selected host entries"),
            tr("Remove <strong>%n</strong> selected host entries?",
               "", selectedItemsCount),
            tr("&Remove"), tr("&Cancel"), QString::null,
            0, 1) != 0) {
        return;
    }

    QSettings settings;
    QStringList hostEntryKeys = settings.value("HostEntryKeys").toStringList();

    Q_FOREACH(QTreeWidgetItem *item,
              ui->entryTreeWidget->selectedItems()) {
            QString key = item->data(0, Qt::UserRole).toString();
            hostEntryKeys.removeAll(key);

            settings.beginGroup("HostEntry-" + key);
            // removes the group, and all it keys
            settings.remove("");
            settings.endGroup();

//            ui->entryTreeWidget->removeItemWidget(item, 0);
        }

    settings.setValue("HostEntryKeys", hostEntryKeys);
    loadHostEntries();
}

/**
 * Removes the selected host entries
 */
void MainWindow::on_actionRemove_selected_host_entries_triggered() {
    removeSelectedHostEntries();
}

/**
 * Stores the hosts file
 */
void MainWindow::on_actionStore_hosts_file_triggered() {
    int itemCount = ui->entryTreeWidget->topLevelItemCount();

    if (itemCount == 0) {
        return;
    }

    QSettings settings;
    QString hostData = QString(HOSTS_PRE_STRING) + "\n\n";

    for (int i = 0; i < itemCount; i++) {
        QTreeWidgetItem *item = ui->entryTreeWidget->topLevelItem(i);

        if (item->checkState(0) == Qt::Unchecked) {
            continue;
        }

        QString key = item->data(0, Qt::UserRole).toString();
        QString name = settings.value(
                hostEntrySettingsKey(key, "Name"), key).toString().trimmed();
        QString data = settings.value(
                hostEntrySettingsKey(key, "Data")).toString().trimmed();

        hostData += "################\n# " + name + "\n################\n";

        if (!data.isEmpty()) {
            hostData += data + "\n\n";
        }
    }

    hostData += QString(HOSTS_POST_STRING) + "\n";

    qDebug() << __func__ << " - 'hostData': " << hostData;

    QString fileName = "/etc/hosts.test";

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << QObject::tr("Could not read hosts file: %1")
                .arg(fileName);

        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");

    // qDebug() << file.size() << in.readAll();
    QString hostsFileText = in.readAll();
    file.close();

    qDebug() << __func__ << " - 'hostsFileText': " << hostsFileText;

    // get regular expression for the encrypted string
    QRegularExpression re = getHostsTextRegularExpression();

    // check if we already have a hosts text
    QRegularExpressionMatch match = re.match(hostsFileText);

    if (match.hasMatch()) {
        hostsFileText.replace(re, hostData);
    } else {
        hostsFileText += "\n\n\n" + hostData;
    }

    qDebug() << __func__ << " - 'hostsFileText': " << hostsFileText;

    // TODO(pbek): write to hosts file
}

/**
 * Returns the regular expression to match hswitch hosts text
 */
QRegularExpression MainWindow::getHostsTextRegularExpression() {
    QRegularExpression re(
            QRegularExpression::escape(HOSTS_PRE_STRING) +
            "\\s+(.+)\\s+" +
            QRegularExpression::escape(HOSTS_POST_STRING));

    re.setPatternOptions(
            QRegularExpression::MultilineOption |
            QRegularExpression::DotMatchesEverythingOption);

    return re;
}