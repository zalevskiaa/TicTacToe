QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# my code
#INCLUDEPATH += "../B_server/"
# end of my code

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../B_server/gamemodel.cpp \
    ../B_server/message.cpp \
    connectwidget.cpp \
    fieldwidget.cpp \
    main.cpp \
    clientwidget.cpp

HEADERS += \
    ../B_server/gamemodel.h \
    ../B_server/message.h \
    clientwidget.h \
    connectwidget.h \
    fieldwidget.h

FORMS += \
    clientwidget.ui \
    connectwidget.ui \
    fieldwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
