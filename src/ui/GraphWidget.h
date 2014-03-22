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
        QList<GraphEdge*>    m_fakeEdges;

        QPoint m_lastCtxtMenuPos;

    private:
        EmployeeNode* getEmployeeNodeById(int id);
        SkillNode*    getSkillNodeById(int id);
        GraphEdge*    getEdge(int sourceNodeId, int destNodeId);

    protected:
        void contextMenuEvent(QContextMenuEvent* event);

    public:
        GraphWidget(QWidget* parent = NULL);

        const QList<EmployeeNode*>& getEmployeeNodes() const;
        const QList<SkillNode*>&    getSkillNodes() const;
        const QList<GraphEdge*>&    getEdges() const;

        void setBestAllocation(const vector< pair<Employee, Skill> >& bestAllocMap);

        ~GraphWidget();

    signals:
        void compute();

    public slots:
        void addNewNode();
        void addEmployeeNode(EmployeeNode* node);
        void addSkillNode(SkillNode* node);
        void clear();
    };
}

#endif // GRAPHWIDGET_H_INCLUDED
