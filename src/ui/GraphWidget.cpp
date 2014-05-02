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
#include "ChangeObjectDialog.h"
#include "DeleteObjectDialog.h"
#include "MainWindow.h"

using namespace bestalloc;

#include "Constants.h"

#include <QSharedPointer>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QDebug>
#include <QMessageBox>

#include <math.h>

GraphWidget::GraphWidget(QWidget* parent)
    : QGraphicsView(parent),
      m_scene(new QGraphicsScene(this)),
      m_employeeNodes(),
      m_skillNodes(),
      m_edges(),
      m_fakeEdges(),
      m_lastCtxtMenuPos(),
      m_resized(false)
{
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(QRectF());
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);

    setContextMenuPolicy(Qt::DefaultContextMenu);
    setDemoData();
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

void GraphWidget::zoomIn()
{
    qreal scaleFactor = 1.02;
    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomOut()
{
    qreal scaleFactor = 1.02;
    scale(1.0/scaleFactor, 1.0/scaleFactor);
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;

        case Qt::Key_Minus:
            zoomOut();
            break;

        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, event->delta() / 1024.0));
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QGraphicsItem* selectedObject = scene()->itemAt(mapToScene(event->pos()), QTransform());
        GraphNode* selectedNode = dynamic_cast<GraphNode*>(selectedObject);
        if (selectedNode == NULL) {
            QMenu contextMenu;

            QAction* addObjectAction = contextMenu.addAction(ADD_OBJECT_MENU_LABEL);
            connect(addObjectAction, SIGNAL(triggered()), SLOT(addObject()));

            QAction* changeObject = contextMenu.addAction(CHANGE_OBJECT_MENU_LABEL);
            connect(changeObject, SIGNAL(triggered()), SLOT(changeObject()));

            QAction* deleteObjectAction = contextMenu.addAction(DELETE_OBJECT_MENU_LABEL);
            connect(deleteObjectAction, SIGNAL(triggered()), SLOT(deleteObject()));

            contextMenu.addSeparator();

            QAction* computeAction = contextMenu.addAction(COMPUTE_LABEL);
            connect(computeAction, SIGNAL(triggered()), SIGNAL(compute()));

            QAction* resetSceneAction = contextMenu.addAction(RESET_GRAPH_LABEL);
            connect(resetSceneAction, SIGNAL(triggered()), SLOT(reset()));

            QAction* generateReportAction = contextMenu.addAction(GENERATE_REPORT_ACTION_MENU_LABEL);
            connect(generateReportAction, SIGNAL(triggered()), SIGNAL(report()));

            contextMenu.exec(event->globalPos());
        }
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100) {
        return;
    }

    scale(scaleFactor, scaleFactor);
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

void GraphWidget::setDemoData()
{
    EmployeeNode* node1 = new EmployeeNode("Peter", QPixmap(":/images/staff_superman.png"), this);
    EmployeeNode* node2 = new EmployeeNode("Mike", QPixmap(":/images/staff_businessman.png"), this);
    EmployeeNode* node3 = new EmployeeNode("Robby", QPixmap(":/images/staff_professor.png"), this);
    EmployeeNode* node4 = new EmployeeNode("James", QPixmap(":/images/staff_old_boss.png"), this);
    EmployeeNode* node5 = new EmployeeNode("Alan", QPixmap(":/images/staff_global_manager.png"), this);

    SkillNode* node6 = new SkillNode("Perl", QPixmap(":/images/res_perl.png"), this);
    SkillNode* node7 = new SkillNode("PHP", QPixmap(":/images/res_php.png"), this);
    SkillNode* node8 = new SkillNode("Ruby", QPixmap(":/images/res_ruby.png"), this);
    SkillNode* node9 = new SkillNode("Python", QPixmap(":/images/res_python.png"), this);
    SkillNode* node10 = new SkillNode("VS 2010", QPixmap(":/images/res_vs.png"), this);

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
    node6->setPos(-300,  200);
    node7->setPos(-150,  200);
    node8->setPos(0,     200);
    node9->setPos(150,   200);
    node10->setPos(300,  200);

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

    scene()->setSceneRect(scene()->itemsBoundingRect());
}

void GraphWidget::resizeToFit()
{
    if (rect().width() < scene()->itemsBoundingRect().width() || rect().height() < scene()->itemsBoundingRect().height()) {
        scene()->setSceneRect(scene()->itemsBoundingRect());
        m_resized = true;
    } else if (m_resized) {
        scene()->setSceneRect(scene()->itemsBoundingRect());
        m_resized = false;
    }
}

void GraphWidget::addObject()
{
    AddNodeDialog* dialog = new AddNodeDialog(this);
    connect(dialog, SIGNAL(addEmployeeNode(EmployeeNode*)), SLOT(addEmployeeNode(EmployeeNode*)));
    connect(dialog, SIGNAL(addSkillNode(SkillNode*)), SLOT(addSkillNode(SkillNode*)));
    connect(dialog, SIGNAL(addEdge(GraphEdge*)), SLOT(addEdge(GraphEdge*)));
    connect(dialog, SIGNAL(updateData(AddNodeDialog*)), SLOT(addNodeDialogUpdateData(AddNodeDialog*)));

    dialog->updateData(m_employeeNodes,m_skillNodes);
    dialog->show();
}

void GraphWidget::changeObject()
{
    ChangeObjectDialog* dialog = new ChangeObjectDialog(this);
    connect(dialog, SIGNAL(updateImage()), SLOT(updateImage()));

    foreach (EmployeeNode *cur, m_employeeNodes) {
        //dialog->addElement(cur);
    }

    foreach (SkillNode *cur, m_skillNodes) {
        //dialog->addElement(cur);
    }

    foreach (GraphEdge *cur, m_edges) {
        //dialog->addElement(cur);
    }

    dialog->show();
}

void GraphWidget::deleteObject()
{
    DeleteObjectDialog* dialog = new DeleteObjectDialog(this);

    foreach (EmployeeNode *cur, m_employeeNodes) {
        //dialog->addElement(cur);
    }

    foreach (SkillNode *cur, m_skillNodes) {
        //dialog->addElement(cur);
    }

    foreach (GraphEdge *cur, m_edges) {
        //dialog->addElement(cur);
    }

    dialog->show();
}

void GraphWidget::addNode(QGraphicsItem *node)
{
    if (node != NULL) {
        EmployeeNode* emplNode;
        emplNode = dynamic_cast<EmployeeNode*>(node);
        if (emplNode != NULL) {
            foreach (EmployeeNode *curNode, m_employeeNodes) {
                if (curNode->getName() == emplNode->getName()) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(WARNING_TITLE);
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setText(ADD_EMPLOYEE_ERROR_TEXT);
                    msgBox.setInformativeText(ADD_EMPLOYEE_ERROR_INFO);
                    msgBox.exec();

                    return;
                }
            }

            m_employeeNodes.push_back(emplNode);
            m_scene->addItem(emplNode);
            emplNode->setPos(m_lastCtxtMenuPos - QPoint(rect().width()/2, rect().height()/2));

            return;
        }

        SkillNode* skillNode;
        skillNode = dynamic_cast<SkillNode*>(node);
        if (skillNode != NULL) {
            foreach (SkillNode* curNode, m_skillNodes) {
                if (curNode->getName() == skillNode->getName()) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(WARNING_TITLE);
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setText(ADD_SKILL_ERROR_TEXT);
                    msgBox.setInformativeText(ADD_SKILL_ERROR_INFO);
                    msgBox.exec();

                    return;
                }
            }

            m_skillNodes.push_back(skillNode);
            m_scene->addItem(skillNode);
            skillNode->setPos(m_lastCtxtMenuPos - QPoint(rect().width()/2, rect().height()/2));

            return;
        }
    }
}

void GraphWidget::addEdge(GraphEdge *edge)
{
    reset();
    foreach (GraphEdge *cur, m_edges) {
        if (cur->getSourceNode() == edge->getSourceNode() && cur->getDestNode() == edge->getDestNode()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle(WARNING_TITLE);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(ADD_EDGE_ERROR_TEXT);
            msgBox.setInformativeText(ADD_EDGE_ERROR_INFO);
            msgBox.exec();

            return;
        }
    }

    m_edges.push_back(edge);
    m_scene->addItem(edge);
}

void GraphWidget::changeNode(QGraphicsItem* node)
{
    if (node != NULL) {


    }
}

void GraphWidget::changeEdge(GraphEdge* edge)
{
    if (edge != NULL) {

    }
}

void GraphWidget::deleteNode(QGraphicsItem* node)
{
    if (node != NULL) {
        reset();

        EmployeeNode* emplNode;
        emplNode = dynamic_cast<EmployeeNode*>(node);
        if (emplNode != NULL) {
            for (int i = 0; i < m_employeeNodes.size(); i++) {
                EmployeeNode* curNode = m_employeeNodes.at(i);
                if (curNode->getId() == emplNode->getId()) {
                    foreach (GraphEdge* edge, curNode->getEdges()) {
                        deleteEdge(edge);
                    }

                    m_employeeNodes.removeAt(i);
                    delete curNode;
                    break;
                }
            }

            return;
        }

        SkillNode* skillNode;
        skillNode = dynamic_cast<SkillNode*>(node);
        if (skillNode != NULL) {
            for (int i = 0; i < m_skillNodes.size(); i++) {
                SkillNode* curNode = m_skillNodes.at(i);
                if (curNode->getId() == skillNode->getId()) {
                    foreach (GraphEdge* edge, curNode->getEdges()) {
                        deleteEdge(edge);
                    }

                    m_skillNodes.removeAt(i);
                    delete curNode;
                    break;
                }
            }

            return;
        }
    }
}

void GraphWidget::deleteEdge(GraphEdge *edge)
{
    if (edge != NULL) {
        reset();

        for (int i = 0; i < m_edges.size(); ++i) {
            GraphEdge* target = m_edges.at(i);
            if (target == edge) {
                target->getSourceNode()->removeEdge(target);
                target->getDestNode()->removeEdge(target);
                m_edges.removeAt(i);

                delete target;
            }
        }
    }
}

void GraphWidget::reset()
{
    foreach (GraphEdge* fakeEdge, m_fakeEdges) {
        m_scene->removeItem(fakeEdge);

        fakeEdge->getSourceNode()->removeEdge(fakeEdge);
        fakeEdge->getDestNode()->removeEdge(fakeEdge);

        delete fakeEdge;
    }

    m_fakeEdges.clear();

    foreach (GraphEdge* edge, m_edges) {
        edge->setMarked(false);
        edge->update();
    }
}

void GraphWidget::clear()
{
    reset();

    foreach (GraphEdge* edge, m_edges) {
        m_scene->removeItem(edge);
    }
    m_edges.clear();

    foreach (EmployeeNode* node, m_employeeNodes) {
        m_scene->removeItem(node);
    }
    m_employeeNodes.clear();

    foreach (SkillNode* node, m_skillNodes) {
        m_scene->removeItem(node);
    }
    m_skillNodes.clear();
}

void GraphWidget::save(QDataStream &str)
{
    /*str << (qint32)m_employeeNodes.size();

    foreach (EmployeeNode *cur, m_employeeNodes) {
        cur->save(str);
    }

    str << (qint32)m_skillNodes.size();

    foreach (SkillNode *cur, m_skillNodes) {
        cur->save(str);
    }

    str << (qint32)m_edges.size();

    foreach (GraphEdge *cur, m_edges) {
        str<<(qint32)cur->getSourceNode()->getId();
        str<<(qint32)cur->getDestNode()->getId();
        cur->save(str);
    }*/
}

void GraphWidget::load(QDataStream &str)
{
    /*clear();

    int size;
    str >> size;
    for (int i = 0; i < size; ++i) {
        EmployeeNode* node = new EmployeeNode("", QPixmap(":/images/staff_superman.png"));
        node->load(str);
        m_employeeNodes.push_back(node);
    }

    str >> size;
    for (int i = 0; i < size; ++i) {
        SkillNode* node = new SkillNode("", QPixmap(":/images/staff_superman.png"));
        node->load(str);
        m_skillNodes.push_back(node);
    }

    str >> size;
    for (int i = 0; i < size; ++i) {
        int eId;
        str >> eId;
        int sId;
        str >> sId;

        EmployeeNode* eNode = getEmployeeNodeById(eId);
        SkillNode* sNode = getSkillNodeById(sId);
        if (!eNode||!sNode) {
            qDebug() << "GraphWidget::load :: !eNode||!sNode\n";
            throw;
        }

        GraphEdge* node = new GraphEdge(eNode,sNode,42);
        node->load(str);
        m_edges.push_back(node);
    }

    foreach (GraphEdge *cur, m_edges) {
        m_scene->addItem(cur);
    }

    foreach (EmployeeNode *cur, m_employeeNodes) {
        m_scene->addItem(cur);
        cur->setPos(cur->getPosition());
    }

    foreach (SkillNode *cur, m_skillNodes) {
        m_scene->addItem(cur);
        cur->setPos(cur->getPosition());
    }*/
}

void GraphWidget::addNodeDialogUpdateData(AddNodeDialog *dlg)
{
    dlg->updateData(m_employeeNodes,m_skillNodes);
}

void GraphWidget::updateImage()
{
    foreach (QGraphicsItem *cur, m_scene->items()) {
        cur->update();
    }
}

/*bool GraphWidget::deleteObject(TaskObject *obj)
{
    reset();

    for (int i = 0; i < m_edges.size(); ++i) {
        GraphEdge *cur = m_edges.at(i);
        if (cur == obj) {
            cur->getSourceNode()->removeEdge(cur);
            cur->getDestNode()->removeEdge(cur);
            m_edges.removeAt(i);
            delete(cur);
            return true;
        }
    }

    for (int i = 0; i < m_employeeNodes.size(); ++i) {
        EmployeeNode *cur = m_employeeNodes.at(i);
        if (cur == obj) {
            foreach (GraphEdge* edge, cur->getEdges()) {
                deleteObject(edge);
            }
            m_employeeNodes.removeAt(i);
            delete(cur);
            return true;
        }
    }

    for (int i = 0; i < m_skillNodes.size(); ++i) {
        SkillNode *cur = m_skillNodes.at(i);
        if (cur == obj) {
            foreach (GraphEdge* edge, cur->getEdges()) {
                deleteObject(edge);
            }

            m_skillNodes.removeAt(i);
            delete(cur);
            return true;
        }
    }

    return false;
}*/

GraphWidget::~GraphWidget()
{
}
