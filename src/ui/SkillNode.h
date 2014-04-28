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
#include "TaskObject.h"

namespace bestalloc
{
    class GraphWidget;

    class SkillNode : public Skill, public GraphNode, public TaskObject
    {
    public:
        SkillNode(const QString& name, const QPixmap& nodePicture, GraphWidget* widget = NULL);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        ~SkillNode();

        void save(QDataStream &str);
        void load(QDataStream &str);

        virtual QString getTaskName();
        virtual void printTo(QLineEdit *editName, QLineEdit *editPower);
        virtual QGraphicsItem *getGraphItem();
        virtual void setFrom(QLineEdit*editName, QLineEdit*editPower);
        virtual void setImage(QGraphicsItem *item);
    };
}

Q_DECLARE_METATYPE(bestalloc::SkillNode*)

#endif // SKILLNODE_H_INCLUDED
