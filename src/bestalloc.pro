QT       += core

QT       -= gui

TARGET   = bestalloc
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ./common ./model ./ui

HEADERS += model/Bigraph.h \
    model/Edge.h \
    model/Employee.h \
    model/Skill.h \
    model/BestAllocAlgo.h \
    model/BigraphIterator.h \
    model/BigraphAllocator.h \
    common/ProjectSession.h

SOURCES += main.cpp \
    model/Employee.cpp \
    model/Skill.cpp \
    model/BestAllocAlgo.cpp \
    common/ProjectSession.cpp
