/*! ---------------------------------------------------------------
 * \file   CSVDataConverter.cpp
 * \brief  CSVDataConverter class implementation
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "CSVDataConverter.h"

using namespace bestalloc;

CSVDataConverter::CSVDataConverter()
{

}

QString CSVDataConverter::convertEmployeeNodes(const QList<EmployeeNode*> &nodes)
{
    QString result = "";
    const QString separator = CSV_SEPARATOR;
    const QString header = separator + "Best Allocation Analyzer report.\n\n";
    const QString employeesNodesSectionOpen = separator + "Employees:\n";
    const QString employeesNodesSectionClose = "\n";
    const QString employeeSeparator = "\n";

    result += header;
    int i = 1;
    result+=employeesNodesSectionOpen;
    foreach (EmployeeNode* node, nodes){
        result+= QString::number(i) + separator + QString::fromStdString(node->getName()) + employeeSeparator;
        i++;
    }
    result+=employeesNodesSectionClose;
    return result;
}

QString CSVDataConverter::convertSkillNodes(const QList<SkillNode*> &nodes)
{
    QString result = "";
    const QString separator = CSV_SEPARATOR;
    const QString skillsNodesSectionOpen = separator + "Skills:\n";
    const QString skillsNodesSectionClose = "\n";
    const QString skillSeparator = "\n";

    result+=skillsNodesSectionOpen;
    int i = 1;
    foreach (SkillNode* node, nodes){
        result+= QString::number(i) + separator + QString::fromStdString(node->getName()) + skillSeparator;
        i++;
    }
    result+=skillsNodesSectionClose;

    return result;
}

QString CSVDataConverter::convertEdges(const QList<GraphEdge*> &edges)
{
    QString result = "";
    const QString separator = CSV_SEPARATOR;
    const QString edgesNodesSectionOpen = separator + "Edges:\n";
    const QString edgesNodesSectionClose = "\n";
    const QString edgeSectionClose = "\n";
    const QString employeeHeader = "Employee";
    const QString skillHeader = "Skill";
    const QString weightHeader = "Weight";


    result+=edgesNodesSectionOpen +
            separator + employeeHeader +
            separator + skillHeader +
            separator + weightHeader +"\n";
    int i = 1;
    foreach (GraphEdge* node, edges){
        result+= QString::number(i) + separator +
                QString::fromStdString(node->getSourceNode()->getName()) + separator +
                QString::fromStdString(node->getDestNode()->getName()) + separator +
                QString::number(node->getWeight()) +
                edgeSectionClose;
        i++;
    }
    result+=edgesNodesSectionClose;

    return result;
}

QString CSVDataConverter::convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap)
{
    QString result = "";
    const QString pairSectionClose = "\n";
    const QString separator = CSV_SEPARATOR;
    const QString bestAllocMapSectionOpen = separator + "Best Allocation:\n";
    const QString bestAllocMapSectionClose = "\n";
    const QString employeeHeader = "Employee";
    const QString skillHeader = "Skill";

    result+=bestAllocMapSectionOpen + separator + employeeHeader + separator + skillHeader + "\n";

    for(int i = 1; i<= bestAllocMap.size(); i++){
        result += QString::number(i) + separator +
                QString::fromStdString(bestAllocMap.at(i-1).first.getName()) + separator +
                QString::fromStdString(bestAllocMap.at(i-1).second.getName()) +
                pairSectionClose;
    }
    result+=bestAllocMapSectionClose;

    return result;
}

CSVDataConverter::~CSVDataConverter()
{

}
