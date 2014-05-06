/*! ---------------------------------------------------------------
 * \file   ReportGenerator.cpp
 * \brief  ReportGenerator class implementation
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "ReportGenerator.h"
using namespace bestalloc;

ReportGenerator::ReportGenerator(const QString &filename, DataConverter *dataConverter):
    m_filename(filename), m_dataConverter(dataConverter)
{

}

void ReportGenerator::setEmployeeNodes(const QList<EmployeeNode*> &nodes)
{
    m_employeeNodes = nodes;
}

void ReportGenerator::setSkillNodes(const QList<SkillNode*> &nodes)
{
    m_skillNodes = nodes;
}

void ReportGenerator::setEdges(const QList<GraphEdge*> & edges)
{
    m_edges = edges;
}

void ReportGenerator::setBestAllocMap(const vector< pair<Employee, Skill> > &bestAllocMap)
{
    m_bestAllocMap = bestAllocMap;
}


void ReportGenerator::generateReport()
{
    QFile* file = new QFile(m_filename);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
        printf("Couldn't open file\n");
    }else{
        QTextStream out(file);
        out << m_dataConverter->convertEmployeeNodes(m_employeeNodes);
        out << m_dataConverter->convertSkillNodes(m_skillNodes);
        out << m_dataConverter->convertEdges(m_edges);
        out << m_dataConverter->convertBestAllocMap(m_bestAllocMap);
    }
    delete file;
}

ReportGenerator::~ReportGenerator()
{

}

