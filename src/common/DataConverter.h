/*! ---------------------------------------------------------------
 * \file   DataConverter.h
 * \brief  DataConverter abstract class declaration
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef DATACONVERTER_H_INCLUDED
#define DATACONVERTER_H_INCLUDED

#include <QList>
#include <QString>
#include <EmployeeNode.h>
#include <SkillNode.h>
#include "GraphEdge.h"

namespace bestalloc
{
    class DataConverter
    {
    public:
        virtual QString convertEmployeeNodes(const QList<EmployeeNode*> &nodes) = 0 ;
        virtual QString convertSkillNodes(const QList<SkillNode*> &nodes) = 0 ;
        virtual QString convertEdges(const QList<GraphEdge*> &edges) = 0 ;
        virtual QString convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap) = 0 ;
        virtual ~DataConverter() {}
    };
}

#endif // DATACONVERTER_H_INCLUDED
