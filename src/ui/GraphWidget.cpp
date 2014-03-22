/*! ---------------------------------------------------------------
 * \file   GraphWidget.cpp
 * \brief  GraphWidget class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "GraphWidget.h"
#include "GraphNode.h"
#include "GraphEdge.h"
#include "AddNodeDialog.h"
#include "DataProvider.h"
#include "BestAllocAlgo.h"
using namespace bestalloc;

#include "Constants.h"

#include <QSharedPointer>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QDebug>

GraphWidget::GraphWidget(QWidget* parent)
    : QGraphicsView(parent),
      m_scene(new QGraphicsScene(this)),
      m_employeeNodes(),
      m_skillNodes(),
      m_edges(),
      m_fakeEdges(),
      m_lastCtxtMenuPos()
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-this->rect().width()/2, -this->rect().height()/2, this->rect().width(), this->rect().height());
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    setContextMenuPolicy(Qt::DefaultContextMenu);

    // TODO delete
    EmployeeNode* node1 = new EmployeeNode("Peter", this, QPixmap(":/images/staff_superman.png"));
    EmployeeNode* node2 = new EmployeeNode("Mike", this, QPixmap(":/images/staff_businessman.png"));
    EmployeeNode* node3 = new EmployeeNode("Robby", this, QPixmap(":/images/staff_professor.png"));
    EmployeeNode* node4 = new EmployeeNode("James", this, QPixmap(":/images/staff_old_boss.png"));
    EmployeeNode* node5 = new EmployeeNode("Alan", this, QPixmap(":/images/staff_global_manager.png"));

    SkillNode*    node6 = new SkillNode("Perl", this, QPixmap(":/images/res_perl.png"));
    SkillNode*    node7 = new SkillNode("PHP", this, QPixmap(":/images/res_php.png"));
    SkillNode*    node8 = new SkillNode("Ruby", this, QPixmap(":/images/res_ruby.png"));
    SkillNode*    node9 = new SkillNode("Python", this, QPixmap(":/images/res_python.png"));
    SkillNode*    node10 = new SkillNode("VS 2010", this, QPixmap(":/images/res_vs.png"));

    m_edges.push_back(new GraphEdge(node1, node6, 7));
    m_edges.push_back(new GraphEdge(node1, node7, 11));
    m_edges.push_back(new GraphEdge(node2, node7, 4));
    m_edges.push_back(new GraphEdge(node2, node10, 3));
    m_edges.push_back(new GraphEdge(node3, node6, 12));
    m_edges.push_back(new GraphEdge(node3, node8, 6));
    m_edges.push_back(new GraphEdge(node4, node7, 10));
    m_edges.push_back(new GraphEdge(node4, node9, 8));
    m_edges.push_back(new GraphEdge(node5, node9, 4));
    m_edges.push_back(new GraphEdge(node5, node10, 6));

    foreach (GraphEdge* edge, m_edges) {
        m_scene->addItem(edge);
    }

    m_scene->addItem(node1);
    m_scene->addItem(node2);
    m_scene->addItem(node3);
    m_scene->addItem(node4);
    m_scene->addItem(node5);
    m_scene->addItem(node6);
    m_scene->addItem(node7);
    m_scene->addItem(node8);
    m_scene->addItem(node9);
    m_scene->addItem(node10);

    node1->setPos(-400, -200);
    node2->setPos(-200, -200);
    node3->setPos(0,    -200);
    node4->setPos(200,  -200);
    node5->setPos(400,  -200);
    node6->setPos(-400,  200);
    node7->setPos(-200,  200);
    node8->setPos(0,     200);
    node9->setPos(200,   200);
    node10->setPos(400,  200);

    m_employeeNodes.push_back(node1);
    m_employeeNodes.push_back(node2);
    m_employeeNodes.push_back(node3);
    m_employeeNodes.push_back(node4);
    m_employeeNodes.push_back(node5);
    m_skillNodes.push_back(node6);
    m_skillNodes.push_back(node7);
    m_skillNodes.push_back(node8);
    m_skillNodes.push_back(node9);
    m_skillNodes.push_back(node10);
}

EmployeeNode* GraphWidget::getEmployeeNodeById(int id)
{
    foreach (EmployeeNode* node, m_employeeNodes) {
        if (node->getId() == id) {
            return node;
        }
    }

    return NULL;
}

SkillNode* GraphWidget::getSkillNodeById(int id)
{
    foreach (SkillNode* node, m_skillNodes) {
        if (node->getId() == id) {
            return node;
        }
    }

    return NULL;
}

GraphEdge* GraphWidget::getEdge(int sourceNodeId, int destNodeId)
{
    foreach (GraphEdge* edge, m_edges) {
        if (edge->getSourceNode()->getId() == sourceNodeId &&
            edge->getDestNode()->getId() == destNodeId)
        {
            return edge;
        }
    }

    return NULL;
}

void GraphWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_lastCtxtMenuPos = QPoint(event->pos());

    QAction* addDataAction = new QAction(NULL);
    addDataAction->setText(ADD_NODE_LABEL);
    connect(addDataAction, SIGNAL(triggered()), SLOT(addNewNode()));

    QAction* computeAction = new QAction(NULL);
    computeAction->setText(COMPUTE_LABEL);
    connect(computeAction, SIGNAL(triggered()), SIGNAL(compute()));

    QAction* clearSceneAction = new QAction(NULL);
    clearSceneAction->setText(CLEAR_SCENE_LABEL);
    connect(clearSceneAction, SIGNAL(triggered()), SLOT(clear()));

    QMenu contextMenu;
    contextMenu.addAction(addDataAction);
    contextMenu.addAction(computeAction);
    contextMenu.addAction(clearSceneAction);

    QPoint globalPos = this->mapToGlobal(event->pos());
    contextMenu.exec(globalPos);
}

const QList<EmployeeNode*>& GraphWidget::getEmployeeNodes() const
{
    return m_employeeNodes;
}

const QList<SkillNode*>& GraphWidget::getSkillNodes() const
{
    return m_skillNodes;
}

const QList<GraphEdge*>& GraphWidget::getEdges() const
{
    return m_edges;
}

void GraphWidget::setBestAllocation(const vector< pair<Employee, Skill> >& bestAllocMap)
{
    for (unsigned int i = 0; i < bestAllocMap.size(); i++) {
        int employeeId = bestAllocMap[i].first.getId();
        int skillId = bestAllocMap[i].second.getId();

        EmployeeNode* sourceNode = getEmployeeNodeById(employeeId);
        SkillNode*    destNode = getSkillNodeById(skillId);

        if (sourceNode != NULL && destNode != NULL) {
            GraphEdge* edge = getEdge(employeeId, skillId);
            if (edge != NULL) {
                edge->setMarked();
                edge->update();
            } else {
                GraphEdge* fakeEdge = new GraphEdge(sourceNode, destNode, 0, true);
                m_fakeEdges.push_back(fakeEdge);
                m_scene->addItem(fakeEdge);
            }
        }
    }
}

void GraphWidget::addNewNode()
{
    AddNodeDialog* dialog = new AddNodeDialog(this);
    connect(dialog, SIGNAL(addEmployeeNode(EmployeeNode*)), SLOT(addEmployeeNode(EmployeeNode*)));
    connect(dialog, SIGNAL(addSkillNode(SkillNode*)), SLOT(addSkillNode(SkillNode*)));
    dialog->show();
}

void GraphWidget::addEmployeeNode(EmployeeNode* node)
{
    m_employeeNodes.push_back(node);
    m_scene->addItem(node);
    node->setPos(m_lastCtxtMenuPos - QPoint(rect().width()/2, rect().height()/2));
}

void GraphWidget::addSkillNode(SkillNode* node)
{
    m_skillNodes.push_back(node);
    m_scene->addItem(node);
    node->setPos(m_lastCtxtMenuPos - QPoint(rect().width()/2, rect().height()/2));
}

void GraphWidget::clear()
{
    foreach (GraphEdge* fakeEdge, m_fakeEdges) {
        m_scene->removeItem(fakeEdge);
    }

    m_fakeEdges.clear();

    foreach (GraphEdge* edge, m_edges) {
        edge->setMarked(false);
        edge->update();
    }
}

GraphWidget::~GraphWidget()
{
}
