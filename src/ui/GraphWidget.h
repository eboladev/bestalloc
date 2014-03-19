/*! ---------------------------------------------------------------
 * \file   GraphWidget.h
 * \brief  GraphWidget class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef GRAPHWIDGET_H_INCLUDED
#define GRAPHWIDGET_H_INCLUDED

#include <QGraphicsView>
#include <QMouseEvent>
#include <QList>

#include "GraphEdge.h"
#include "GraphNode.h"
#include "EmployeeNode.h"
#include "SkillNode.h"

namespace bestalloc
{
    class GraphWidget : public QGraphicsView
    {
        Q_OBJECT

    private:
        QGraphicsScene*      m_scene;
        QList<EmployeeNode*> m_employeeNodes;
        QList<SkillNode*>    m_skillNodes;
        QList<GraphEdge*>    m_edges;

    public:
        GraphWidget(QWidget* parent = NULL);
        ~GraphWidget();

    public slots:
        void addNewNode();
        void compute();
        void showContextMenu(const QPoint& pos);
    };
}

#endif // GRAPHWIDGET_H_INCLUDED
