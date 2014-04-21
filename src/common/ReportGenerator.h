/*! ---------------------------------------------------------------
 * \file   ReportGenerator.cpp
 * \brief  ReportGenerator class declaration
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <vector>
#include "EmployeeNode.h"
#include "SkillNode.h"
#include "GraphEdge.h"
#include "DataConverter.h"

namespace bestalloc
{
    class ReportGenerator
    {
    private:
        QString m_filename;

        DataConverter *m_dataConverter;
        QList<EmployeeNode*> m_employeeNodes;
        QList<SkillNode*> m_skillNodes;
        QList<GraphEdge*> m_edges;
        vector< pair<Employee, Skill> > m_bestAllocMap;

    public:
        ReportGenerator(const QString &filename, DataConverter *dataConverter);

        void setEmployeeNodes(const QList<EmployeeNode*> &nodes);
        void setSkillNodes(const QList<SkillNode*> &nodes);
        void setEdges(const QList<GraphEdge*> & edges);
        void setBestAllocMap(const vector< pair<Employee, Skill> > &bestAllocMap);

        void generateReport();

        ~ReportGenerator();
    };
}

#endif // REPORTGENERATOR_H
