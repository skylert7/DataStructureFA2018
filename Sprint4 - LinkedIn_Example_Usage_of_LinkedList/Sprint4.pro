TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Driver.cpp \
    testcases.cpp \
    main.cpp

HEADERS += \
    catch.hpp \
    Driver.h \
    dsvector.hpp \
    Node.h \
    Stack.hpp \
    AdjList.hpp \
    LinkedList.hpp
