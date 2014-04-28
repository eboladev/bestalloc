/*! ---------------------------------------------------------------
 * \file   EmployeeNode.h
 * \brief  EmployeeNode class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef EMPLOYEENODE_H_INCLUDED
#define EMPLOYEENODE_H_INCLUDED

#include "Employee.h"
#include "GraphNode.h"
#include "TaskObject.h"

namespace bestalloc
{
    class GraphWidget;
    class Employee;

    class EmployeeNode : public Employee, public GraphNode, public TaskObject
    {
    public:
        EmployeeNode(const QString& name, const QPixmap& nodePicture, GraphWidget* widget = NULL);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        ~EmployeeNode();

        void save(QDataStream &str);
        void load(QDataStream &str);

        virtual QString getTaskName();
        virtual void printTo(QLineEdit *editName, QLineEdit *editPower);
        virtual QGraphicsItem *getGraphItem();
        virtual void setFrom(QLineEdit*editName, QLineEdit*editPower);
        virtual void setImage(QGraphicsItem *item);
    };
}
Q_DECLARE_METATYPE(bestalloc::EmployeeNode*)

#endif // EMPLOYEENODE_H_INCLUDED
