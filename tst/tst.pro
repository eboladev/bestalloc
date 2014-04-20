TARGET = test
TEMPLATE = app

QT+=widgets

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
    ../src/ui/AddNodeDialog.h \
    ../src/common/XMLDataConverter.h \
    ../src/common/TextDataConverter.h \
    ../src/common/ReportGenerator.h \
    ../src/common/DataConverter.h \
    ../src/common/CSVDataConverter.h \
    ../src/ui/TaskObject.h \
    ../src/ui/DeleteObjectDialog.h \
    ../src/ui/ChangeObjectDialog.h \
    ../src/ui/AddEdgeDialog.h



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
    ../src/ui/AddNodeDialog.cpp \
    ../src/common/XMLDataConverter.cpp \
    ../src/common/TextDataConverter.cpp \
    ../src/common/ReportGenerator.cpp \
    ../src/common/CSVDataConverter.cpp \
    ../src/ui/TaskObject.cpp \
    ../src/ui/DeleteObjectDialog.cpp \
    ../src/ui/ChangeObjectDialog.cpp \
    ../src/ui/AddEdgeDialog.cpp



CONFIG += qtestlib
QT += testlib \
        widgets

OTHER_FILES += \
    BestAllocAlgo.o
