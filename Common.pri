
HEADERS += \
    $$PWD/Common/GrpcHeader.h \
    $$PWD/Common/MsgCenter.h \
    $$PWD/PBFiles/*.h

SOURCES += \
    $$PWD/Common/MsgCenter.cpp \
    $$PWD/PBFiles/*.cc


INCLUDEPATH += \
    $$HEADERS \
    /usr/local/include

LIBS += \
    /usr/local/lib/*.a

