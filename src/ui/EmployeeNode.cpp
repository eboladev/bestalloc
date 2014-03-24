/*! ---------------------------------------------------------------
 * \file   EmployeeNode.cpp
 * \brief  EmployeeNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "EmployeeNode.h"
#include "GraphWidget.h"
using namespace bestalloc;

static int s_globalEmployeeCounter = 0;

EmployeeNode::EmployeeNode(const QString &name, const QPixmap &nodePicture)
    : Employee(s_globalEmployeeCounter++, name.toStdString()), GraphNode(nodePicture)
{
}

void EmployeeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphNode::paint(painter, option, widget);

    painter->setBrush(Qt::black);
    painter->setFont(QFont("Verdana", 15));

    painter->drawText(QRect(-100, -140, 100, 50), Qt::AlignCenter | Qt::AlignTop, QString(getName().c_str()));
}

EmployeeNode::~EmployeeNode()
{
}

