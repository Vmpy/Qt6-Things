QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += $$PWD/inc

SOURCES += \
    src/abbrlistwidget.cpp \
    src/abbrlistwidgetitem.cpp \
    src/confirmpage.cpp \
    src/drawcommands.cpp \
    src/drawtoolbar.cpp \
    src/drawwidget.cpp \
    src/imginfodialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mymediaplayer.cpp \
    src/opentreethread.cpp \
    src/picanimationwidget.cpp \
    src/picbutton.cpp \
    src/picshow.cpp \
    src/picstatebutton.cpp \
    src/projsetpage.cpp \
    src/projtree.cpp \
    src/projtreeitem.cpp \
    src/projtreethread.cpp \
    src/projtreewidget.cpp \
    src/removeprojdialog.cpp \
    src/slideshowdialog.cpp \
    src/watermarkdialog.cpp \
    src/wizard.cpp

HEADERS += \
    inc/abbrlistwidget.h \
    inc/abbrlistwidgetitem.h \
    inc/confirmpage.h \
    inc/const.h \
    inc/drawcommands.h \
    inc/drawtoolbar.h \
    inc/drawwidget.h \
    inc/imginfodialog.h \
    inc/mainwindow.h \
    inc/mymediaplayer.h \
    inc/opentreethread.h \
    inc/picanimationwidget.h \
    inc/picbutton.h \
    inc/picshow.h \
    inc/picstatebutton.h \
    inc/projsetpage.h \
    inc/projtree.h \
    inc/projtreeitem.h \
    inc/projtreethread.h \
    inc/projtreewidget.h \
    inc/removeprojdialog.h \
    inc/slideshowdialog.h \
    inc/watermarkdialog.h \
    inc/wizard.h

FORMS += \
    layout/confirmpage.ui \
    layout/mainwindow.ui \
    layout/picshow.ui \
    layout/projsetpage.ui \
    layout/projtree.ui \
    layout/removeprojdialog.ui \
    layout/slideshowdialog.ui \
    layout/wizard.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc

RC_ICONS = "icon/albumplayer.ico"
