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

namespace bestalloc
{
    class GraphWidget;
    class Employee;
    class EmployeeNode : public Employee, public GraphNode
    {
    public:
        EmployeeNode(const QString& name, const QPixmap& nodePicture);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        ~EmployeeNode();

        void save(QDataStream &str);
        void load(QDataStream &str);
    };
}

#endif // EMPLOYEENODE_H_INCLUDED
