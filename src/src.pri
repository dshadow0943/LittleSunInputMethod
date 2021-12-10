include (keyboard/keyboard.pri)
include (train/train.pri)
include (widget/widget.pri)

INCLUDEPATH += \
        $$PWD/keyboard \
        $$PWD/train \
        $$PWD/widget \

INCLUDEPATH += \
        $$PWD/keyboard \
        $$PWD/train \

SOURCES += \
    $$PWD/centercontroller.cpp \
    $$PWD/keyboardAdaptor.cpp \
    $$PWD/main.cpp \
    $$PWD/globalapplication.cpp \
    $$PWD/mousethread.cpp

FORMS += \
    $$PWD/centercontroller.ui

HEADERS += \
    $$PWD/centercontroller.h \
    $$PWD/keyboardAdaptor.h \
    $$PWD/globalapplication.h \
    $$PWD/mousethread.h

RESOURCES += \
    $$PWD/res/res.qrc




