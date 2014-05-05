/*! ---------------------------------------------------------------
 * \file   GraphNode.h
 * \brief  GraphNode class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef GRAPHNODE_H_INCLUDED
#define GRAPHNODE_H_INCLUDED

#include <QGraphicsItem>

namespace bestalloc
{
    class GraphWidget;
    class GraphEdge;

    class GraphNode : public QGraphicsItem
    {
    private:
        QPixmap           m_nodePicture;
        QList<GraphEdge*> m_edgeList;
        QPointF           m_position;

    protected:
        GraphWidget*      m_widget;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    public:
        GraphNode(const QPixmap& nodePicture, GraphWidget* widget = NULL);

        void addEdge(GraphEdge *edge);
        QList<GraphEdge*> getEdges() const;

        QPixmap getNodePicture() const;
        void setNodePicture(const QPixmap& value);

        QPointF getPosition() const;
        void setPosition(const QPointF& value);

        bool advance();

        QRectF boundingRect() const;
        QPainterPath shape() const;
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

        void removeEdge(GraphEdge *edge);

        virtual ~GraphNode();
    };
}

#endif // GRAPHNODE_H_INCLUDED
