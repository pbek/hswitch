/*
 * Copyright (c) 2017 Patrizio Bekerle -- http://www.bekerle.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include "mainwindow.h"
#include "version.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QString appNameAdd = "";

#ifdef QT_DEBUG
    appNameAdd = "-debug";
#endif

    QCoreApplication::setOrganizationDomain("PBEK");
    QCoreApplication::setOrganizationName("PBEK");
    QCoreApplication::setApplicationName("hswitch" + appNameAdd);

    QString appVersion = QString(VERSION);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 4, 0))
    appVersion += " " + QSysInfo::prettyProductName();

    if (!appVersion.contains(QSysInfo::currentCpuArchitecture())) {
        appVersion += " " + QSysInfo::currentCpuArchitecture();
    }
#else
    appVersion += " Qt " + QString(QT_VERSION_STR);
#endif

#ifdef QT_DEBUG
    appVersion += " Debug";
#endif

    QCoreApplication::setApplicationVersion(appVersion);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
