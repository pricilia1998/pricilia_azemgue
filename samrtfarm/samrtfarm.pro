#-------------------------------------------------
#
# Project created by QtCreator 2020-02-28T09:35:06
#
#-------------------------------------------------

QT       += core gui sql
QT += printsupport charts qml quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = samrtfarm
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

SOURCES += \
        main.cpp \
    tache.cpp \
    connexion.cpp \
    employe.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    tahaa.cpp \
    mainwindow.cpp \
    fournisseur.cpp \
    nourriture.cpp \
    template.cpp \
    animal.cpp \
    carte.cpp \
    notification.cpp \
    qcustomplot.cpp \
    sirine.cpp \
    recolte.cpp \
    sabrine.cpp \
    smtp.cpp \
    zone.cpp

HEADERS += \
    tache.h \
    connexion.h \
    employe.h \
    drilldownchart.h \
    drilldownslice.h \
    tache.h \
    tahaa.h \
    mainwindow.h \
    fournisseur.h \
    nourriture.h \
    template.h \
    animal.h \
    carte.h \
    notification.h \
    qcustomplot.h \
    sirine.h \
    recolte.h \
    sabrine.h \
    smtp.h \
    zone.h

FORMS += \
    tahaa.ui \
    mainwindow.ui \
    template.ui \
    sirine.ui \
    sabrine.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
