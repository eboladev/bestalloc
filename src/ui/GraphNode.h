/*! ---------------------------------------------------------------
 * \file   GraphNode.h
 * \brief  GraphNode class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef GRAPHNODE_H_INCLUDED
#define GRAPHNODE_H_INCLUDED

#include <QGraphicsWidget>

namespace bestalloc
{
    class GraphWidget;
    class GraphEdge;

    class GraphNode : public QGraphicsPixmapItem
    {
    private:
        GraphWidget*      m_graph;
        QPixmap           m_nodePicture;
        QPointF           m_newPos;
        QList<GraphEdge*> m_edgeList;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    public:
        GraphNode(GraphWidget *graphWidget, const QPixmap& nodePicture);

        void addEdge(GraphEdge *edge);
        QList<GraphEdge*> getEdges() const;

        bool advance();

        QRectF boundingRect() const;
        QPainterPath shape() const;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        virtual ~GraphNode();
    };
}

#endif // GRAPHNODE_H_INCLUDED
