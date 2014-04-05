TARGET = test
TEMPLATE = app

INCLUDEPATH = . ../src/common ../src/model ../src/ui

HEADERS += ../src/model/Skill.h \
    Test_Skill.h \
    Test_Skill.h



SOURCES += ../src/model/Skill.cpp \
    main.cpp \
    Test_Skill.cpp



CONFIG += qtestlib
QT += testlib
