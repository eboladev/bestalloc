TARGET = test
TEMPLATE = app

INCLUDEPATH = . ../src/common ../src/model ../src/ui

HEADERS += ../src/model/Skill.h \
    Test_Skill.h \
    Test_Skill.h \
    Test_Employee.h \
    Test_Edge.h \
    Test_BestAllocAlgo.h \
    ../src/model/Employee.h \
    ../src/model/Edge.h \
    ../src/model/BigraphIterator.h \
    ../src/model/BigraphAllocator.h \
    ../src/model/Bigraph.h \
    ../src/model/BestAllocAlgo.h \
    ../src/common/DataProvider.h \
    ../src/common/Constants.h \
    ../src/common/ConfigReader.h \
    ../src/ui/SkillNode.h \
    ../src/ui/MainWindow.h \
    ../src/ui/GraphWidget.h \
    ../src/ui/GraphNode.h \
    ../src/ui/GraphEdge.h \
    ../src/ui/EmployeeNode.h \
    ../src/ui/AddNodeDialog.h



SOURCES += ../src/model/Skill.cpp \
    main.cpp \
    Test_Skill.cpp \
    Test_Employee.cpp \
    Test_Edge.cpp \
    Test_BestAllocAlgo.cpp \
    ../src/model/Employee.cpp \
    ../src/model/BestAllocAlgo.cpp \
    ../src/common/DataProvider.cpp \
    ../src/common/ConfigReader.cpp \
    ../src/ui/SkillNode.cpp \
    ../src/ui/MainWindow.cpp \
    ../src/ui/GraphWidget.cpp \
    ../src/ui/GraphNode.cpp \
    ../src/ui/GraphEdge.cpp \
    ../src/ui/EmployeeNode.cpp \
    ../src/ui/AddNodeDialog.cpp



CONFIG += qtestlib
QT += testlib \
        widgets

OTHER_FILES += \
    BestAllocAlgo.o
