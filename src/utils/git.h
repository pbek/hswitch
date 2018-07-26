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

#pragma once

/*  Miscellaneous functions that can be useful */

namespace Utils {
    namespace Git {
        void commitCurrentNoteFolder();
        bool executeCommand(QString command, QProcess *process = Q_NULLPTR);
        bool executeGitCommand(QString arguments,
                               QProcess *process = Q_NULLPTR);
        QString gitCommand();
        void showLog(QString filePath);
        bool hasLogCommand();
        bool isCurrentNoteFolderUseGit();
    }
}
