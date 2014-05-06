/*! ---------------------------------------------------------------
 * \file   TextDataConverter.cpp
 * \brief  TextDataConverter class implementation
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "TextDataConverter.h"

using namespace bestalloc;

TextDataConverter::TextDataConverter()
{

}

QString TextDataConverter::convertEmployeeNodes(const QList<EmployeeNode*> &nodes)
{
    QString result = "";
    const QString header = "Best Allocation Analyzer report.\n\n";
    const QString employeesNodesSectionOpen = "Employees: \n";
    const QString employeesNodesSectionClose = ".\n\n";
    const QString employeeSeparator = ", ";
    result += header;
    result+=employeesNodesSectionOpen;
    foreach (EmployeeNode* node, nodes){
        result+= QString::fromStdString(node->getName()) + employeeSeparator;
    }
    result.remove(result.length() - employeeSeparator.length(), employeeSeparator.length());
    result+=employeesNodesSectionClose;
    return result;
}

QString TextDataConverter::convertSkillNodes(const QList<SkillNode*> &nodes)
{
    QString result = "";
    const QString skillsNodesSectionOpen = "Skills: \n";
    const QString skillsNodesSectionClose = ".\n\n";
    const QString skillSeparator = ", ";

    result+=skillsNodesSectionOpen;
    foreach (SkillNode* node, nodes){
        result+= QString::fromStdString(node->getName()) + skillSeparator;
    }
    result.remove(result.length()-skillSeparator.length(), skillSeparator.length());
    result+=skillsNodesSectionClose;

    return result;
}

QString TextDataConverter::convertEdges(const QList<GraphEdge*> &edges)
{
    QString result = "";
    const QString edgesNodesSectionOpen = "Edges: \n";
    const QString edgesNodesSectionClose = ".\n\n";
    const QString edgeSectionOpen = "(";
    const QString edgeSectionClose = "), \n";
    const QString separator = ", ";

    result+=edgesNodesSectionOpen;
    foreach (GraphEdge* node, edges){
        result+= edgeSectionOpen +
                QString::fromStdString(node->getSourceNode()->getName()) + separator +
                QString::fromStdString(node->getDestNode()->getName()) + separator +
                QString::number(node->getWeight()) +
                edgeSectionClose;
    }
    result.remove(result.length()-separator.length() -1, separator.length() + 1);
    result+=edgesNodesSectionClose;

    return result;
}

QString TextDataConverter::convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap)
{
    QString result = "";
    const QString bestAllocMapSectionOpen = "Best Allocation: \n";
    const QString bestAllocMapSectionClose = ".\n\n";
    const QString pairSectionOpen = "(";
    const QString pairSectionClose = "), \n";
    const QString separator = ", ";

    result+=bestAllocMapSectionOpen;
    for(int i = 0; i< bestAllocMap.size(); i++){
        result += pairSectionOpen +
                QString::fromStdString(bestAllocMap.at(i).first.getName()) + separator +
                QString::fromStdString(bestAllocMap.at(i).second.getName()) +
                pairSectionClose;
    }
    result.remove(result.length()-separator.length() -1, separator.length() + 1);
    result+=bestAllocMapSectionClose;

    return result;
}

TextDataConverter::~TextDataConverter()
{

}
