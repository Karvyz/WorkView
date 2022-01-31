QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity.cpp \
    addaction.cpp \
    addevent.cpp \
    addproduct.cpp \
    adduser.cpp \
    dbservice.cpp \
    main.cpp \
    workview.cpp

HEADERS += \
    activity.h \
    addaction.h \
    addevent.h \
    addproduct.h \
    adduser.h \
    dbservice.h \
    workview.h

FORMS += \
    addaction.ui \
    addevent.ui \
    addproduct.ui \
    adduser.ui \
    workview.ui

TRANSLATIONS += \
    WorkView_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
