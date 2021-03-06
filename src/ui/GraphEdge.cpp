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
#include "Constants.h"
using namespace bestalloc;

#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QDebug>

#include <math.h>

GraphEdge::GraphEdge(EmployeeNode* sourceNode, SkillNode* destNode, int weight, bool isMarked)
    : QGraphicsItem(), m_sourceNode(sourceNode), m_destNode(destNode), m_weight(weight), m_isMarked(isMarked)
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

    if (m_isMarked) {
        painter->setPen(QPen(Qt::red, 3.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter->setPen(QPen(Qt::black, 1.5, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    }

    painter->drawLine(line);

    painter->setPen(QPen(Qt::darkBlue, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setFont(QFont("Verdana", 12));

    QPoint weightPosPoint = QPoint((m_destPoint.x() + m_sourcePoint.x()) / 2, (m_destPoint.y() + m_sourcePoint.y()) / 2);

    painter->drawText(QRect(weightPosPoint.x() - 50, weightPosPoint.y(), 100, 20), Qt::AlignCenter | Qt::AlignTop, QString::number(m_weight));
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

void GraphEdge::setSourceNode(EmployeeNode* value)
{
    m_sourceNode = value;
}

void GraphEdge::setDestNode(SkillNode* value)
{
    m_destNode = value;
}

void GraphEdge::setWeight(int value)
{
    m_weight = value;
}

void GraphEdge::setMarked(bool isMarked)
{
    m_isMarked = isMarked;
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

bool GraphEdge::compare(GraphEdge* first, GraphEdge* second)
{
    if (first == NULL || second == NULL) return false;

    EmployeeNode* firstSrcNode = first->getSourceNode();
    EmployeeNode* secondSrcNode = second->getSourceNode();

    if (firstSrcNode == NULL || secondSrcNode == NULL) return false;

    QString firstName = QString::fromStdString(firstSrcNode->getName());
    QString secondName = QString::fromStdString(secondSrcNode->getName());

    if (firstName.compare(secondName, Qt::CaseSensitive) >= 0) {
        return false;
    } else {
        return true;
    }
}

GraphEdge::~GraphEdge()
{
}
