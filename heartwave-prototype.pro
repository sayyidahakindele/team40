#-------------------------------------------------
#
# Project created by QtCreator 2021-03-10T20:15:39
#
#-------------------------------------------------
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = denas-prototype
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

source_dir = src
forms_dir = ui
resources_dir = res

QMAKE_CLEAN += denas.db

SOURCES += \
        $${source_dir}/main.cpp \
        $${source_dir}/mainwindow.cpp \
        $${source_dir}/scores.cpp \
        $${source_dir}/settings.cpp \
        $${source_dir}/testdata.cpp \
        $${source_dir}/qcustomplot.cpp \

HEADERS += \
        $${source_dir}/session.h \
        $${source_dir}/mainwindow.h \
        $${source_dir}/scores.h \
        $${source_dir}/settings.h \
        $${source_dir}/loghistory.h \
        $${source_dir}/testdata.h \
        $${source_dir}/qcustomplot.h \

FORMS += \
        $${forms_dir}/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    $${resources_dir}/denas.qrc

OBJECTS_DIR = .qt/obj
MOC_DIR = .qt/moc
UI_DIR = .qt/ui
RCC_DIR = .qt/resources
DESTDIR = .
