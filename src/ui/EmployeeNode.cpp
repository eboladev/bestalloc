/*! ---------------------------------------------------------------
 * \file   EmployeeNode.cpp
 * \brief  EmployeeNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "EmployeeNode.h"
#include "GraphWidget.h"
#include "ConfigReader.h"
using namespace bestalloc;

static int s_globalEmployeeCounter = 0;

EmployeeNode::EmployeeNode(const QString &name, const QPixmap &nodePicture, GraphWidget* widget)
    : Employee(s_globalEmployeeCounter++, name.toStdString()), GraphNode(nodePicture, widget), TaskObject()
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

void EmployeeNode::save(QDataStream &str)
{
    this->Employee::save(str);
    this->GraphNode::save(str);
}

void EmployeeNode::load(QDataStream &str)
{
    this->Employee::load(str);
    this->GraphNode::load(str);
}

QString EmployeeNode::getTaskName()
{
    return getName().data();
}

void EmployeeNode::printTo(QLineEdit *editName, QLineEdit *editPower)
{
    editName->setEnabled(true);
    editPower->setEnabled(false);
    editName->setText(getName().data());
}

QGraphicsItem *EmployeeNode::getGraphItem()
{
    return new QGraphicsPixmapItem(getPixmap());
    return NULL;
}

void EmployeeNode::setFrom(QLineEdit *editName, QLineEdit *editPower)
{
    string newName = ConfigReader::readString(editName->text());
    setName(newName);
}

void EmployeeNode::setImage(QGraphicsItem *item)
{
    GraphNode::setImage(item);
}
