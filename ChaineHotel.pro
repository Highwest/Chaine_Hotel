#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T22:37:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChaineHotel
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
        chainehotel.cpp \
    personnel.cpp \
    hoteldb.cpp \
    tableaudebord.cpp \
    parametrecourant.cpp \
    hotel.cpp \
    gestionclient.cpp \
    client.cpp \
    ajoutclient.cpp \
    modifclient.cpp \
    gestionpersonnel.cpp \
    ajoutpersonnel.cpp \
    modifpersonnel.cpp

HEADERS += \
        chainehotel.h \
    personnel.h \
    hoteldb.h \
    tableaudebord.h \
    parametrecourant.h \
    hotel.h \
    gestionclient.h \
    client.h \
    ajoutclient.h \
    modifclient.h \
    gestionpersonnel.h \
    ajoutpersonnel.h \
    modifpersonnel.h

FORMS += \
        chainehotel.ui \
    tableaudebord.ui \
    parametrecourant.ui \
    gestionclient.ui \
    ajoutclient.ui \
    modifclient.ui \
    gestionpersonnel.ui \
    ajoutpersonnel.ui \
    modifpersonnel.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc

DISTFILES +=
