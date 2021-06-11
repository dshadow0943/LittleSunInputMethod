
include (keyboard/keyboard.pri)
include (train/train.pri)

INCLUDEPATH += \
        $$PWD/keyboard \
        $$PWD/train \

SOURCES += \
    $$PWD/centercontroller.cpp \
    $$PWD/keyboardAdaptor.cpp \
    $$PWD/main.cpp

FORMS += \
    $$PWD/centercontroller.ui

HEADERS += \
    $$PWD/centercontroller.h \
    $$PWD/keyboardAdaptor.h

RESOURCES += \
    $$PWD/res/res.qrc




