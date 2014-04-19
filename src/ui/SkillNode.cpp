/*! ---------------------------------------------------------------
 * \file   SkillNode.cpp
 * \brief  SkillNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "SkillNode.h"
#include "GraphWidget.h"
#include "ConfigReader.h"
using namespace bestalloc;

static int s_globalSkillCounter = 0;

SkillNode::SkillNode(const QString &name, const QPixmap &nodePicture)
    : Skill(s_globalSkillCounter++, name.toStdString()), GraphNode(nodePicture), TaskObject()
{
}

void SkillNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphNode::paint(painter, option, widget);

    painter->setBrush(Qt::black);
    painter->setFont(QFont("Verdana", 15));

    painter->drawText(QRect(-100, -140, 100, 50), Qt::AlignCenter | Qt::AlignTop, QString(getName().c_str()));
}

SkillNode::~SkillNode()
{
}

void SkillNode::save(QDataStream &str)
{
    this->Skill::save(str);
    this->GraphNode::save(str);
}

void SkillNode::load(QDataStream &str)
{
    this->Skill::load(str);
    this->GraphNode::load(str);
}

QString SkillNode::getTaskName()
{
    return getName().data();
}

void SkillNode::printTo(QLineEdit *editName, QLineEdit *editPower)
{
    editName->setEnabled(true);
    editPower->setEnabled(false);
    editName->setText(getName().data());
}

QGraphicsItem *SkillNode::getGraphItem()
{
    return new QGraphicsPixmapItem(getPixmap());
}

void SkillNode::setFrom(QLineEdit *editName, QLineEdit *editPower)
{
    string newName = ConfigReader::readString(editName->text());
    setName(newName);
}

void SkillNode::setImage(QGraphicsItem *item)
{
    GraphNode::setImage(item);
}
