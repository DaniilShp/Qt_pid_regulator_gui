QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PID.cpp \
    accuracy.cpp \
    accuracyform.cpp \
    pidregulatorform.cpp \
    settingsform.cpp \
    simulation.cpp \
    startmenu.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    PID.h \
    accuracy.h \
    accuracyform.h \
    pidregulatorform.h \
    settingsform.h \
    simulation.h \
    startmenu.h \
    mainwindow.h

FORMS += \
    accuracyform.ui \
    pidregulatorform.ui \
    settingsform.ui \
    startmenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
