TARGET   = bestalloc
TEMPLATE = app

INCLUDEPATH += ./common ./model ./ui

QT+=widgets

HEADERS += model/Bigraph.h \
    model/Edge.h \
    model/Employee.h \
    model/Skill.h \
    model/BestAllocAlgo.h \
    model/BigraphIterator.h \
    model/BigraphAllocator.h \
    common/DataProvider.h \
    ui/MainWindow.h \
    ui/GraphWidget.h \
    common/Constants.h \
    ui/GraphEdge.h \
    ui/GraphNode.h \
    ui/AddNodeDialog.h \
    ui/SkillNode.h \
    ui/EmployeeNode.h \
    common/ConfigReader.h \
    ui/ChangeObjectDialog.h \
    ui/TaskObject.h \
    ui/DeleteObjectDialog.h \
    ui/AddEdgeDialog.h \
    common/XMLDataConverter.h \
    common/TextDataConverter.h \
    common/ReportGenerator.h \
    common/DataConverter.h \
    common/CSVDataConverter.h

SOURCES += main.cpp \
    model/Employee.cpp \
    model/Skill.cpp \
    model/BestAllocAlgo.cpp \
    common/DataProvider.cpp \
    ui/MainWindow.cpp \
    ui/GraphWidget.cpp \
    ui/GraphEdge.cpp \
    ui/GraphNode.cpp \
    ui/AddNodeDialog.cpp \
    ui/SkillNode.cpp \
    ui/EmployeeNode.cpp \
    common/ConfigReader.cpp \
    ui/ChangeObjectDialog.cpp \
    ui/TaskObject.cpp \
    ui/DeleteObjectDialog.cpp \
    ui/AddEdgeDialog.cpp \
    common/XMLDataConverter.cpp \
    common/TextDataConverter.cpp \
    common/ReportGenerator.cpp \
    common/CSVDataConverter.cpp

RESOURCES += \
    bestalloc.qrc
