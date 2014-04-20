/*! ---------------------------------------------------------------
 * \file   XMLDataConverter.h
 * \brief  XMLDataConverter class declaration
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#ifndef XMLDATACONVERTER_H
#define XMLDATACONVERTER_H

#include "DataConverter.h"

namespace bestalloc{
    class XMLDataConverter : public DataConverter
    {
    public:
        XMLDataConverter();

        virtual QString convertEmployeeNodes(const QList<EmployeeNode*> &nodes);
        virtual QString convertSkillNodes(const QList<SkillNode*> &nodes);
        virtual QString convertEdges(const QList<GraphEdge*> &edges);
        virtual QString convertBestAllocMap(const vector< pair <Employee, Skill> > &bestAllocMap);
        ~XMLDataConverter();

    };
}
#endif // XMLDATACONVERTER_H
