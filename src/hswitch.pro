#
# Copyright (c) 2016-2018 Patrizio Bekerle -- http://www.bekerle.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hswitch
TEMPLATE = app

CODECFORTR = UTF-8
CONFIG += c++11

SOURCES += main.cpp\
        utils/misc.cpp \
        utils/git.cpp \
        utils/gui.cpp \
        utils/schema.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h\
            utils/misc.h \
            utils/git.h \
            utils/gui.h \
            utils/schema.h \
            version.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

include(libraries/qmarkdowntextedit/qmarkdowntextedit.pri)

unix {

  isEmpty(PREFIX) {
    PREFIX = /usr
  }

  isEmpty(BINDIR) {
    BINDIR = $$PREFIX/bin
  }

  isEmpty(DATADIR) {
    DATADIR = $$PREFIX/share
  }

  INSTALLS += target desktop icons

  target.path = $$INSTROOT$$BINDIR

  desktop.path = $$DATADIR/applications
  desktop.files += hswitch.desktop

  icons.path = $$DATADIR/icons/hicolor
  icons.files += images/icons/*
}
