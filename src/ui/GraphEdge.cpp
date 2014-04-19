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
#include "ConfigReader.h"

#include <math.h>

GraphEdge::GraphEdge(EmployeeNode* sourceNode, SkillNode* destNode, int weight, bool isMarked)
    : m_sourceNode(sourceNode), m_destNode(destNode), m_weight(weight), m_isMarked(isMarked), TaskObject()
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

    painter->drawText(QRect(weightPosPoint.x() - 20, weightPosPoint.y(), 20, 20), Qt::AlignCenter | Qt::AlignTop, QString::number(m_weight));
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

void GraphEdge::save(QDataStream &str)
{
    str<<(qint32)m_weight;
    str<<m_isMarked;

    ConfigReader::saveQPointF(str, m_sourcePoint);
    ConfigReader::saveQPointF(str, m_destPoint);
}

void GraphEdge::load(QDataStream &str)
{
    str>>m_weight;
    str>>m_isMarked;

    ConfigReader::loadQPointF(str, m_sourcePoint);
    ConfigReader::loadQPointF(str, m_destPoint);
}

QString GraphEdge::getTaskName()
{
    QString result = "";
    result+=m_sourceNode->getName().data();
    result+="<->";
    result+=m_destNode->getName().data();
    return result;
}

void GraphEdge::printTo(QLineEdit *editName, QLineEdit *editPower)
{
    editName->setEnabled(false);
    editPower->setEnabled(true);
    editName->clear();
    editPower->setText(QString::number(m_weight));
}

void GraphEdge::setFrom(QLineEdit *editName, QLineEdit *editPower)
{
    m_weight = editPower->text().toInt();
}
