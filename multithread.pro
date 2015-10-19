TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    request.cpp \
    stopper.cpp \
    waiting_queue.cpp \
    ready_queue.cpp

HEADERS += \
    request.hpp \
    stopper.hpp \
    waiting_queue.hpp \
    ready_queue.hpp

