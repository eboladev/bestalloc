/*! ---------------------------------------------------------------
 * \file   SkillNode.h
 * \brief  SkillNode class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef SKILLNODE_H_INCLUDED
#define SKILLNODE_H_INCLUDED

#include "Skill.h"
#include "GraphNode.h"

namespace bestalloc
{
    class GraphWidget;

    class SkillNode : public Skill, public GraphNode
    {
    public:
        SkillNode(const QString& name, const QPixmap& nodePicture);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        ~SkillNode();
    };
}

#endif // SKILLNODE_H_INCLUDED
