TARGET = test
TEMPLATE = app

INCLUDEPATH = . ../src/common ../src/model ../src/ui

HEADERS += ../src/model/Skill.h \
    Test_Skill.h \
    Test_Skill.h \
    ../src/model/Employee.h \
    Test_Employee.h \
    Test_BestAllocAlgo.h \
    ../src/model/BestAllocAlgo.h \
    Test_Edge.h \
    ../src/model/Edge.h



SOURCES += ../src/model/Skill.cpp \
    main.cpp \
    Test_Skill.cpp \
    ../src/model/Employee.cpp \
    Test_Employee.cpp \
    Test_BestAllocAlgo.cpp \
    ../src/model/BestAllocAlgo.cpp \
    Test_Edge.cpp



CONFIG += qtestlib
QT += testlib
