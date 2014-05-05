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
    common/Constants.h \
    common/DataProvider.h \
    common/XMLDataConverter.h \
    common/TextDataConverter.h \
    common/ReportGenerator.h \
    common/DataConverter.h \
    common/CSVDataConverter.h \
    common/ConfigReader.h \
    ui/MainWindow.h \
    ui/GraphWidget.h \
    ui/GraphEdge.h \
    ui/GraphNode.h \
    ui/SkillNode.h \
    ui/EmployeeNode.h \
    ui/ChangeObjectDialog.h \
    ui/DeleteObjectDialog.h \
    ui/AddObjectDialog.h \
    ui/EditNodeDialog.h \
    common/BestAllocException.h

SOURCES += main.cpp \
    model/Employee.cpp \
    model/Skill.cpp \
    model/BestAllocAlgo.cpp \
    common/DataProvider.cpp \
    common/XMLDataConverter.cpp \
    common/TextDataConverter.cpp \
    common/ReportGenerator.cpp \
    common/CSVDataConverter.cpp \
    common/ConfigReader.cpp \
    ui/MainWindow.cpp \
    ui/GraphWidget.cpp \
    ui/GraphEdge.cpp \
    ui/GraphNode.cpp \
    ui/SkillNode.cpp \
    ui/EmployeeNode.cpp \
    ui/ChangeObjectDialog.cpp \
    ui/DeleteObjectDialog.cpp \
    ui/AddObjectDialog.cpp \
    ui/EditNodeDialog.cpp \
    common/BestAllocException.cpp

RESOURCES += \
    bestalloc.qrc
