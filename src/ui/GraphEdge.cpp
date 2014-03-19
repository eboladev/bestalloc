/*! ---------------------------------------------------------------
 * \file   GraphEdge.cpp
 * \brief  GraphEdge class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "GraphEdge.h"
#include "EmployeeNode.h"
#include "SkillNode.h"
using namespace bestalloc;

#include <QPainter>
#include <QDebug>

#include <math.h>

GraphEdge::GraphEdge(EmployeeNode* sourceNode, SkillNode* destNode, int weight)
    : m_sourceNode(sourceNode), m_destNode(destNode), m_weight(weight)
{
    setAcceptedMouseButtons(0);
    m_sourceNode->addEdge(this);
    m_destNode->addEdge(this);
    adjust();
}

QRectF GraphEdge::boundingRect() const
{
    if (m_sourceNode == NULL || m_destNode == NULL) {
        return QRectF();
    }

    qreal penWidth = 1;
    qreal extra = (penWidth + 20.0) / 2.0;

    return QRectF(m_sourcePoint, QSizeF(m_destPoint.x() - m_sourcePoint.x(),
                                        m_destPoint.y() - m_sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void GraphEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (m_sourceNode == NULL || m_destNode == NULL) {
        return;
    }

    QLineF line(m_sourcePoint, m_destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.0))) {
        return;
    }

    painter->setPen(QPen(Qt::black, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

EmployeeNode* GraphEdge::getSourceNode() const
{
    return m_sourceNode;
}

SkillNode* GraphEdge::getDestNode() const
{
    return m_destNode;
}

int GraphEdge::getWeight() const
{
    return m_weight;
}

void GraphEdge::adjust()
{
    if (m_sourceNode == NULL || m_destNode == NULL) {
        return;
    }

    qreal srcNodeWidth = m_sourceNode->boundingRect().width() - 5;
    qreal srcNodeHeight = m_sourceNode->boundingRect().height() - 5;

    qreal destNodeWidth = m_destNode->boundingRect().width() - 5;
    qreal destNodeHeight = m_destNode->boundingRect().height() - 5;

    QLineF line(mapFromItem(m_sourceNode, -srcNodeWidth / 2, -srcNodeHeight / 2),
                mapFromItem(m_destNode, -destNodeWidth / 2, -destNodeHeight / 2));

    prepareGeometryChange();

    if (line.length() > qreal(20.0)) {
        double angle = acos(line.dx() / line.length());
        if (line.dy() < 0) {
            angle = 2 * M_PI - angle;
        }

        qreal srcRadius = sqrt(srcNodeWidth/2 * srcNodeWidth/2 + srcNodeHeight/2 * srcNodeHeight/2);
        qreal destRadius = sqrt(destNodeWidth/2 * destNodeWidth/2 + destNodeHeight/2 * destNodeHeight/2);

        m_sourcePoint = line.p1() + QPointF(cos(angle) * srcRadius, sin(angle) * srcRadius);
        m_destPoint = line.p2() - QPointF(cos(angle) * destRadius, sin(angle) * destRadius);
    } else {
        m_sourcePoint = m_destPoint = line.p1();
    }
}
