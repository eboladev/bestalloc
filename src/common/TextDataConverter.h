/*! ---------------------------------------------------------------
 * \file   TextDataConverter.h
 * \brief  TextDataConverter class declaration
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef TEXTDATACONVERTER_H_INCLUDED
#define TEXTDATACONVERTER_H_INCLUDED

#include "DataConverter.h"

namespace bestalloc
{
    class TextDataConverter : public DataConverter
    {
    public:
        TextDataConverter();

        QString convertEmployeeNodes(const QList<EmployeeNode*> &nodes);
        QString convertSkillNodes(const QList<SkillNode*> &nodes);
        QString convertEdges(const QList<GraphEdge*> &edges);
        QString convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap);

        ~TextDataConverter();
    };
}

#endif // TEXTDATACONVERTER_H_INCLUDED
