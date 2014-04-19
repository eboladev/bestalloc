/*! ---------------------------------------------------------------
 * \file   TaskObject.h
 * \brief  TaskObject class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef TASKOBJECT_H
#define TASKOBJECT_H

#include <QString>
#include <QMetaType>
#include <QLineEdit>
#include <QGraphicsItem>

namespace bestalloc
{
    class TaskObject
    {
    public:
        TaskObject();
        ~TaskObject();
        virtual QString getTaskName();
        virtual void printTo(QLineEdit*editName,QLineEdit*editPower);
        virtual QGraphicsItem *getGraphItem();
        virtual void setFrom(QLineEdit*editName,QLineEdit*editPower);
        virtual void setImage(QGraphicsItem *item);
    };
}
Q_DECLARE_METATYPE(bestalloc::TaskObject*)

#endif // TASKOBJECT_H
