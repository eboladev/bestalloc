/*! ---------------------------------------------------------------
 * \file   GraphEdge.h
 * \brief  GraphEdge class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef GRAPHEDGE_H_INCLUDED
#define GRAPHEDGE_H_INCLUDED

#include <QGraphicsItem>


namespace bestalloc
{
    class EmployeeNode;
    class SkillNode;

    class GraphEdge : public QGraphicsItem
    {
    private:
        EmployeeNode* m_sourceNode;
        SkillNode*    m_destNode;
        int           m_weight;

        QPointF m_sourcePoint;
        QPointF m_destPoint;

    protected:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    public:
        GraphEdge(EmployeeNode* sourceNode, SkillNode* destNode, int weight);

        EmployeeNode* getSourceNode() const;
        SkillNode*    getDestNode() const;
        int           getWeight() const;

        void adjust();
    };
}

#endif // GRAPHEDGE_H_INCLUDED
