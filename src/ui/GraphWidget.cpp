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
using namespace bestalloc;

#include <iostream>
using namespace std;


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
      m_edges()
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(-this->rect().width()/2, -this->rect().height()/2, this->rect().width(), this->rect().height());
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    // TODO delete

    BestAllocAlgorithm algo;
    algo.addEmployee(Employee(1, "Peter"));
    algo.addEmployee(Employee(2, "Mike"));
    algo.addEmployee(Employee(3, "Robby"));
    algo.addEmployee(Employee(4, "James"));
    algo.addEmployee(Employee(5, "Alan"));

    algo.addSkill(Skill(1, "C++"));
    algo.addSkill(Skill(2, "Java"));
    algo.addSkill(Skill(3, "Python"));
    algo.addSkill(Skill(4, "Ruby"));
    algo.addSkill(Skill(5, "Perl"));

    algo.assignSkill(1, 1, 7);
    algo.assignSkill(1, 2, 11);

    algo.assignSkill(2, 2, 4);
    algo.assignSkill(2, 5, 3);

    algo.assignSkill(3, 1, 12);
    algo.assignSkill(3, 3, 6);

    algo.assignSkill(4, 2, 10);
    algo.assignSkill(4, 4, 8);

    algo.assignSkill(5, 4, 4);
    algo.assignSkill(5, 5, 6);



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

    node1->setPos(-300, -150);
    node2->setPos(-150, -150);
    node3->setPos(0,    -150);
    node4->setPos(150,  -150);
    node5->setPos(300,  -150);
    node6->setPos(-300,  150);
    node7->setPos(-150,   150);
    node8->setPos(0,     150);
    node9->setPos(150,   150);
    node10->setPos(300,  150);

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

void GraphWidget::addNewNode()
{
    AddNodeDialog* dialog = new AddNodeDialog();
    dialog->show();
}

void GraphWidget::compute()
{
    // TODO delete

    DataProvider controller;

    foreach (EmployeeNode* node, m_employeeNodes) {
        controller.addEmployee(*node);
    }

    foreach (SkillNode* node, m_skillNodes) {
        controller.addSkill(*node);
    }

    foreach (GraphEdge* edge, m_edges) {
        controller.assignSkill(edge->getSourceNode()->getId(), edge->getDestNode()->getId(), edge->getWeight());
    }

    vector< pair<Employee, Skill> > bestAllocMap = controller.getBestAllocation();

    cout << "Best allocation:" << endl;
    vector< pair<Employee, Skill> >::iterator i;
    for (i = bestAllocMap.begin(); i != bestAllocMap.end(); i++) {
        cout << i->first.getName() << " <---> " << i->second.getName() << endl;
    }
}

void GraphWidget::showContextMenu(const QPoint &pos)
{
    QAction* addDataAction = new QAction(NULL);
    addDataAction->setText(ADD_NODE_LABEL);
    connect(addDataAction, SIGNAL(triggered()), SLOT(addNewNode()));

    QAction* computeAction = new QAction(NULL);
    computeAction->setText(COMPUTE_LABEL);
    connect(computeAction, SIGNAL(triggered()), SLOT(compute()));

    QMenu contextMenu;
    contextMenu.addAction(addDataAction);
    contextMenu.addAction(computeAction);

    QPoint globalPos = this->mapToGlobal(pos);
    contextMenu.exec(globalPos);
}

GraphWidget::~GraphWidget()
{
}
