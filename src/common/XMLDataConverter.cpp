/*! ---------------------------------------------------------------
 * \file   XMLDataConverter.cpp
 * \brief  XMLDataConverter class implementation
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "XMLDataConverter.h"

using namespace bestalloc;

XMLDataConverter::XMLDataConverter()
{

}

QString XMLDataConverter::convertEmployeeNodes(const QList<EmployeeNode*> &nodes)
{
    QString result = "";
    const QString header = "<XML>\n";
    const QString tabulation = "    ";                          //4 spaces
    const QString employeesNodesSectionOpen = "<Employees>\n";
    const QString employeesNodesSectionClose = "</Employees>\n";
    const QString employeeSectionOpen = tabulation + "<Employee>";
    const QString employeeSectionClose = "</Employee>\n";

    result +=header;

    result+=employeesNodesSectionOpen;
    foreach (EmployeeNode* node, nodes){
        result+= employeeSectionOpen + QString::fromStdString(node->getName()) + employeeSectionClose;
    }
    result+=employeesNodesSectionClose;
    return result;
}

QString XMLDataConverter::convertSkillNodes(const QList<SkillNode*> &nodes)
{
    QString result = "";
    const QString tabulation = "    ";                      //4 spaces
    const QString skillsNodesSectionOpen = "<Skills>\n";
    const QString skillsNodesSectionClose = "</Skills>\n";
    const QString skillSectionOpen = tabulation + "<Skill>";
    const QString skillSectionClose = "</Skill>\n";

    result+=skillsNodesSectionOpen;
    foreach (SkillNode* node, nodes){
        result+= skillSectionOpen + QString::fromStdString(node->getName()) + skillSectionClose;
    }
    result+=skillsNodesSectionClose;

    return result;
}

QString XMLDataConverter::convertEdges(const QList<GraphEdge*> &edges)
{
    QString result = "";
    const QString tabulation = "    ";                      //4 spaces
    const QString edgesNodesSectionOpen = "<Edges>\n";
    const QString edgesNodesSectionClose = "</Edges>\n";
    const QString edgeSectionOpen = tabulation + "<Edge>\n";
    const QString edgeSectionClose = tabulation + "</Edge>\n";
    const QString skillSectionOpen = tabulation + tabulation + "<Skill>";
    const QString skillSectionClose = "</Skill>\n";
    const QString employeeSectionOpen = tabulation + tabulation + "<Employee>";
    const QString employeeSectionClose = "</Employee>\n";
    const QString weightSectionOpen = tabulation + tabulation + "<Weight>";
    const QString weightSectionClose = "</Weight>\n";

    result+=edgesNodesSectionOpen;
    foreach (GraphEdge* node, edges){
        result+= edgeSectionOpen +
                employeeSectionOpen + QString::fromStdString(node->getSourceNode()->getName()) + employeeSectionClose +
                skillSectionOpen +QString::fromStdString(node->getDestNode()->getName()) + skillSectionClose +
                weightSectionOpen +QString::number(node->getWeight()) +weightSectionClose +
                edgeSectionClose;
    }
    result+=edgesNodesSectionClose;

    return result;
}

QString XMLDataConverter::convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap)
{
    QString result = "";
    const QString tabulation = "    ";                      //4 spaces
    const QString bestAllocMapSectionOpen = "<Best_Allocation>\n";
    const QString bestAllocMapSectionClose = "</Best_Allocation>\n";
    const QString pairSectionOpen = tabulation + "<Pair>\n";
    const QString pairSectionClose = tabulation + "</Pair>\n";
    const QString skillSectionOpen = tabulation + tabulation + "<Skill>";
    const QString skillSectionClose = "</Skill>\n";
    const QString employeeSectionOpen = tabulation + tabulation + "<Employee>";
    const QString employeeSectionClose = "</Employee>\n";
    const QString tale = "</XML>";

    result += bestAllocMapSectionOpen;
    for(int i = 0; i< bestAllocMap.size(); i++){
        result+= pairSectionOpen +
                employeeSectionOpen + QString::fromStdString(bestAllocMap.at(i).first.getName()) + employeeSectionClose +
                skillSectionOpen +QString::fromStdString(bestAllocMap.at(i).second.getName()) + skillSectionClose +
                pairSectionClose;
    }
    result += bestAllocMapSectionClose;
    result += tale;
    return result;
}

XMLDataConverter::~XMLDataConverter()
{

}

