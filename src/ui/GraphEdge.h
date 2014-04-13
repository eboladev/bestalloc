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
        bool          m_isMarked;

        QPointF m_sourcePoint;
        QPointF m_destPoint;

    protected:
        QRectF boundingRect() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    public:
        GraphEdge(EmployeeNode* sourceNode, SkillNode* destNode, int weight, bool isMarked = false);

        EmployeeNode* getSourceNode() const;
        SkillNode*    getDestNode() const;
        int           getWeight() const;

        void setSourceNode(EmployeeNode* value);
        void setDestNode(SkillNode* value);
        void setWeight(int value);
        void setMarked(bool isMarked = true);

        void adjust();

        void save(QDataStream &str);
        void load(QDataStream &str);
    };
}

#endif // GRAPHEDGE_H_INCLUDED
