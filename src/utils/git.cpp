/*
 * Copyright (c) 2014-2018 Patrizio Bekerle -- http://www.bekerle.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 */

#include <QDebug>
#include <QProcess>
#include <QtCore/QSettings>
#include "git.h"
#include "misc.h"


/**
 * Executes a command
 *
 * @param command
 * @param process
 * @return
 */
bool Utils::Git::executeCommand(QString command, QProcess *process) {
    if (process == Q_NULLPTR) {
        process = new QProcess();
    }

    process->start(command);

    if (!process->waitForFinished()) {
        qWarning() << "Command '" + command + "' failed";
        return false;
    }

//    QByteArray result = process->readAll();

//    if (!result.isEmpty()) {
//    qDebug() << "Result message by '" + command + "': " + result;
//    }

    QByteArray errorMessage = process->readAllStandardError();

    if (!errorMessage.isEmpty()) {
        qWarning() << "Error message by '" + command + "': " + errorMessage;
    }

    return true;
}

/**
 * Executes a git command
 *
 * @param arguments
 * @param process
 * @return
 */
bool Utils::Git::executeGitCommand(QString arguments, QProcess *process) {
    return executeCommand("\""+ gitCommand() + "\" " + arguments, process);
}

/**
 * Returns the git command
 *
 * @return
 */
QString Utils::Git::gitCommand() {
    QSettings settings;
    QString path = settings.value("gitExecutablePath").toString();

    if (path.isEmpty()) {
#ifdef Q_OS_WIN
        path = "git.exe";
#else
        path = "git";
#endif
    }

    return path;
}

/**
 * Checks if a git log command is set
 *
 * @return
 */
bool Utils::Git::hasLogCommand() {
    QSettings settings;
    return !settings.value("gitLogCommand").toString().isEmpty();
}
