TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    01_hello_SDL.cpp \
    ltexture.cpp

LIBS += -L/usr/local/lib -lSDL2 -lSDL2_image -ldl -lpthread
INCLUDES += /usr/local/include

HEADERS += \
    ltexture.h
