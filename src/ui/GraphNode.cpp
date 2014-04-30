/*! ---------------------------------------------------------------
 * \file   GraphNode.cpp
 * \brief  GraphNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "GraphNode.h"
#include "GraphWidget.h"
#include "GraphEdge.h"
using namespace bestalloc;

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QMenu>
#include <QAction>
#include "ConfigReader.h"

GraphNode::GraphNode(const QPixmap& nodePicture, GraphWidget* widget)
    : QGraphicsItem(), m_widget(widget), m_nodePicture(QPixmap(nodePicture)), m_position(QPointF(0,0))
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void GraphNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);

    if (m_widget != NULL) {
        m_widget->resizeToFit();
    }
}

QVariant GraphNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionHasChanged:
            foreach (GraphEdge *edge, m_edgeList) {
                edge->adjust();
            }

            break;

        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void GraphNode::addEdge(GraphEdge *edge)
{
    m_edgeList << edge;
    edge->adjust();
}

QList<GraphEdge*> GraphNode::getEdges() const
{
    return m_edgeList;
}

bool GraphNode::advance()
{
    if (m_newPos == pos())
        return false;

    setPos(m_newPos);
    return true;
}

QRectF GraphNode::boundingRect() const
{
    qreal adjust = 5;
    return QRectF(-100 - adjust, -130 - adjust, 100 + adjust, 130 + adjust);
}

QPainterPath GraphNode::shape() const
{
    QPainterPath path;
    path.addEllipse(-150, -150, 150, 150);
    return path;
}

void GraphNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->drawPixmap(-100, -100, 100, 100, m_nodePicture);
}

void GraphNode::save(QDataStream &str)
{
    m_position.setX(QGraphicsItem::x());
    m_position.setY(QGraphicsItem::y());
    ConfigReader::saveQPixmap(str,m_nodePicture);
    ConfigReader::saveQPointF(str,m_newPos);
    ConfigReader::saveQPointF(str,m_position);
}

void GraphNode::load(QDataStream &str)
{
    ConfigReader::loadQPixmap(str,m_nodePicture);
    ConfigReader::loadQPointF(str,m_newPos);
    ConfigReader::loadQPointF(str,m_position);
}

void GraphNode::setPos(qreal x, qreal y)
{
    QGraphicsItem::setPos(x,y);
}

void GraphNode::setPos(const QPointF &arg)
{
    QGraphicsItem::setPos(arg);
}

QPointF GraphNode::getPosition()
{
    return m_position;
}

QPixmap GraphNode::getPixmap()
{
    return m_nodePicture;
}

void GraphNode::setImage(QGraphicsItem *image)
{
    m_nodePicture = ((QGraphicsPixmapItem*)image)->pixmap();
}

bool GraphNode::hasEdges()
{
    return m_edgeList.size();
}

void GraphNode::removeEdge(GraphEdge *edge)
{
    m_edgeList.removeAll(edge);
}

GraphNode::~GraphNode()
{
}
