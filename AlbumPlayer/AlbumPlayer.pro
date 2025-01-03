QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abbrlistwidget.cpp \
    abbrlistwidgetitem.cpp \
    confirmpage.cpp \
    main.cpp \
    mainwindow.cpp \
    mymediaplayer.cpp \
    opentreethread.cpp \
    picanimationwidget.cpp \
    picbutton.cpp \
    picshow.cpp \
    picstatebutton.cpp \
    projsetpage.cpp \
    projtree.cpp \
    projtreeitem.cpp \
    projtreethread.cpp \
    projtreewidget.cpp \
    removeprojdialog.cpp \
    slideshowdialog.cpp \
    wizard.cpp

HEADERS += \
    abbrlistwidget.h \
    abbrlistwidgetitem.h \
    confirmpage.h \
    const.h \
    mainwindow.h \
    mymediaplayer.h \
    opentreethread.h \
    picanimationwidget.h \
    picbutton.h \
    picshow.h \
    picstatebutton.h \
    projsetpage.h \
    projtree.h \
    projtreeitem.h \
    projtreethread.h \
    projtreewidget.h \
    removeprojdialog.h \
    slideshowdialog.h \
    wizard.h

FORMS += \
    confirmpage.ui \
    mainwindow.ui \
    picshow.ui \
    projsetpage.ui \
    projtree.ui \
    removeprojdialog.ui \
    slideshowdialog.ui \
    wizard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

RC_ICONS = "icon/albumplayer.ico"
