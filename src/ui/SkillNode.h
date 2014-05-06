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
    protected:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    public:
        SkillNode(const QString& name, const QPixmap& nodePicture, GraphWidget* widget = NULL);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        static bool compare(SkillNode* first, SkillNode* second);

        ~SkillNode();
    };
}

Q_DECLARE_METATYPE(bestalloc::SkillNode*)

#endif // SKILLNODE_H_INCLUDED
