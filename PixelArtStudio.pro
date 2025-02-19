QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = PixelArtStudio

CONFIG += c++17

SOURCES += main.cpp \
           mainwindow.cpp \
           canvaswidget.cpp \
           pluginmanager.cpp \
           themeswitcher.cpp

HEADERS += mainwindow.h \
           canvaswidget.h \
           plugininterface.h \
           pluginmanager.h \
           themeswitcher.h

RESOURCES += resources.qrc

# Enable high DPI scaling
QT += core5compat
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_NO_CAST_TO_ASCII
DEFINES += QT_NO_CAST_FROM_ASCII

# Enable translations
TRANSLATIONS += translations/zh_CN.ts \
                translations/en_US.ts \
                translations/ja_JP.ts

# Enable plugins
CONFIG += plugin

# Enable styles/themes
CONFIG += styles

# Enable debugging
CONFIG += debug_and_release
CONFIG += debug
