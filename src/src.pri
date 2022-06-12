include (keyboard/keyboard.pri)
include (train/train.pri)
include (widget/widget.pri)
include (configure/configure.pri)

INCLUDEPATH += \
        $$PWD/keyboard \
        $$PWD/train \
        $$PWD/widget \
        $$PWD/configure \
        $$PWD \

SOURCES += \
    $$PWD/centercontroller.cpp \
    $$PWD/keyboardAdaptor.cpp \
    $$PWD/main.cpp \
    $$PWD/globalapplication.cpp \
    $$PWD/mousethread.cpp \
    $$PWD/globalsignaltransfer.cpp

FORMS += \
    $$PWD/centercontroller.ui

HEADERS += \
    $$PWD/centercontroller.h \
    $$PWD/keyboardAdaptor.h \
    $$PWD/globalapplication.h \
    $$PWD/mousethread.h \
    $$PWD/globalconfig.h \
    $$PWD/globalsignaltransfer.h

RESOURCES += \
    $$PWD/res/res.qrc




