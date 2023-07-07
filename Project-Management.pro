QT       += core gui

QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lws2_32

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminscreen.cpp \
    encryption.cpp \
    ganttchart.cpp \
    kanbanboard.cpp \
    kanbanwidget.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    notification.cpp \
    projectobjects.cpp \
    taskmodal.cpp

HEADERS += \
    adminscreen.h \
    encryption.h \
    ganttchart.h \
    kanbanboard.h \
    kanbanwidget.h \
    login.h \
    mainwindow.h \
    notification.h \
    projectobjects.h \
    taskmodal.h

FORMS += \
    adminscreen.ui \
    ganttchart.ui \
    kanbanboard.ui \
    kanbanwidget.ui \
    login.ui \
    mainwindow.ui \
    notification.ui \
    taskmodal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

