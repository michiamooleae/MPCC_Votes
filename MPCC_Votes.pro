TARGET = MPCC_Votes
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QMAKE_MAC_SDK = macosx10.12

HEADERS += httpretriever.h \
    mpcc.h \
    uncroppedimagesfinder.h

SOURCES += main.cpp \
    httpretriever.cpp \
    mpcc.cpp \
    uncroppedimagesfinder.cpp

macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/curl/7.46.0/lib/ -lcurl

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/curl/7.46.0/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/curl/7.46.0/include

