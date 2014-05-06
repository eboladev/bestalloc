/*! ---------------------------------------------------------------
 * \file   CSVDataConverter.h
 * \brief  CSVDataConverter class declaration
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CSVDATACONVERTER_H_INCLUDED
#define CSVDATACONVERTER_H_INCLUDED

#include "DataConverter.h"
#include "Constants.h"

namespace bestalloc
{
    class CSVDataConverter : public DataConverter
    {
    public:
        CSVDataConverter();

        QString convertEmployeeNodes(const QList<EmployeeNode*> &nodes);
        QString convertSkillNodes(const QList<SkillNode*> &nodes);
        QString convertEdges(const QList<GraphEdge*> &edges);
        QString convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap);

        ~CSVDataConverter();
    };
}

#endif // CSVDATACONVERTER_H_INCLUDED
