QT       += core

QT       -= gui

TARGET   = bestalloc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./inc

HEADERS += inc/Bigraph.h \
    inc/Edge.h \
    inc/Employee.h \
    inc/ProjectSession.h \
    inc/Skill.h \
    inc/BestAllocAlgo.h \
    inc/BigraphIterator.h \
    inc/BigraphAllocator.h

SOURCES += src/main.cpp \
    src/Employee.cpp \
    src/Skill.cpp \
    src/ProjectSession.cpp \
    src/BestAllocAlgo.cpp
