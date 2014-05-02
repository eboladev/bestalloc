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
#include "AddNodeDialog.h"

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
        bool   m_resized;

    private:
        EmployeeNode* getEmployeeNodeById(int id);
        SkillNode*    getSkillNodeById(int id);
        GraphEdge*    getEdge(int sourceNodeId, int destNodeId);

        void zoomIn();
        void zoomOut();

        void scaleView(qreal scaleFactor);

    protected:
        void keyPressEvent(QKeyEvent *event);
        void wheelEvent(QWheelEvent* event);
        void mousePressEvent(QMouseEvent* event);

    public:
        GraphWidget(QWidget* parent = NULL);

        void setEmployeeNodes(const QList<EmployeeNode*>& nodes);
        void setSkillNodes(const QList<SkillNode*>& nodes);
        void setEdges(const QList<GraphEdge*>& edges);

        const QList<EmployeeNode*>& getEmployeeNodes() const;
        const QList<SkillNode*>&    getSkillNodes() const;
        const QList<GraphEdge*>&    getEdges() const;

        void setBestAllocation(const vector< pair<Employee, Skill> >& bestAllocMap);
        void setDemoData();

        ~GraphWidget();

    public slots:
        void resizeToFit();

        void addNewNode();
        void changeObject();
        void deleteObject();

        void addNode(QGraphicsItem* node);
        void addEdge(GraphEdge* edge);

        void changeNode(QGraphicsItem* node);
        void changeEdge(GraphEdge* edge);

        void deleteNode(QGraphicsItem* node);
        void deleteEdge(GraphEdge* edge);

        void reset();
        void clear();

        void save(QDataStream &str);
        void load(QDataStream &str);

        void addNodeDialogUpdateData(AddNodeDialog*dlg);
        void updateImage();
    };
}

#endif // GRAPHWIDGET_H_INCLUDED
