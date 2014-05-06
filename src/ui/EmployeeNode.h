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

#include <QtAlgorithms>

namespace bestalloc
{
    class GraphWidget;

    class EmployeeNode : public Employee, public GraphNode
    {
    protected:
        void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

    public:
        EmployeeNode(const QString& name, const QPixmap& nodePicture, GraphWidget* widget = NULL);

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        static bool compare(EmployeeNode* first, EmployeeNode* second);

        ~EmployeeNode();
    };
}

Q_DECLARE_METATYPE(bestalloc::EmployeeNode*)

#endif // EMPLOYEENODE_H_INCLUDED
