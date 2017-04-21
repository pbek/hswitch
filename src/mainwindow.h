#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>

#define HOSTS_PRE_STRING "### BEGIN HSWITCH HOSTS ###"
#define HOSTS_POST_STRING "### END HSWITCH HOSTS ###"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_entry_triggered();

    void on_actionQuit_triggered();

    void on_entryTreeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_entryTreeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_entryTextEdit_textChanged();

    void on_entryTreeWidget_customContextMenuRequested(const QPoint &pos);

    void on_actionRemove_selected_host_entries_triggered();

    void on_actionStore_hosts_file_triggered();

private:
    Ui::MainWindow *ui;

    QString generateUuid() const;

    void loadHostEntries() const;

    QTreeWidgetItem *
    createHostEntryTreeWidgetItem(const QString &key,
                                      const QString &name,
                                      bool enabled = false) const;

    const QString hostEntrySettingsKey(const QString &key, QString variableName) const;

    void removeSelectedHostEntries();

    QRegularExpression getHostsTextRegularExpression();
};

#endif // MAINWINDOW_H
