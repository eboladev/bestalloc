/*! ---------------------------------------------------------------
 * \file   SkillNode.cpp
 * \brief  SkillNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "SkillNode.h"
#include "GraphWidget.h"
using namespace bestalloc;

static int s_globalSkillCounter = 0;

SkillNode::SkillNode(const QString &name, const QPixmap &nodePicture)
    : Skill(s_globalSkillCounter++, name.toStdString()), GraphNode(nodePicture)
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
