/*! ---------------------------------------------------------------
 * \file   DeleteObjectDialog.cpp
 * \brief  DeleteObjectDialog class implementation
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "DeleteObjectDialog.h"
#include "GraphWidget.h"
#include "Constants.h"
using namespace bestalloc;

#include <QPushButton>
#include <QLayout>
#include <QStyleFactory>
#include <QMessageBox>
#include <QtAlgorithms>

DeleteObjectDialog::DeleteObjectDialog(GraphWidget* parent)
    : QDialog(parent),
      m_widget(parent)
{
    m_objectsList = new QComboBox(this);
    m_objectsList->setStyle(QStyleFactory::create("Windows"));
    connect(m_objectsList, SIGNAL(currentIndexChanged(int)), SLOT(selectObject(int)));

    QPushButton* confirmButton = new QPushButton(DELETE_LABEL, this);
    connect(confirmButton, SIGNAL(clicked()), SLOT(deleteObject()));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* layoutBtns = new QHBoxLayout;
    layoutBtns->addWidget(confirmButton);
    layoutBtns->addWidget(closeButton);

    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(m_objectsList);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(DELETE_OBJECT_LABEL);

    updateContent();
}

void DeleteObjectDialog::updateContent()
{
    m_objectsList->clear();

    QList<EmployeeNode*> employees = m_widget->getEmployeeNodes();
    qSort(employees.begin(), employees.end(), EmployeeNode::compare);
    foreach (EmployeeNode* emplNode, employees) {
        QVariant var = QVariant::fromValue(emplNode);
        m_objectsList->addItem(EMPLOYEE_ID + QString::fromStdString(emplNode->getName()), var);
    }

    QList<SkillNode*> skills = m_widget->getSkillNodes();
    qSort(skills.begin(), skills.end(), SkillNode::compare);
    foreach (SkillNode* skillNode, skills) {
        QVariant var = QVariant::fromValue(skillNode);
        m_objectsList->addItem(SKILL_ID + QString::fromStdString(skillNode->getName()), var);
    }

    QList<GraphEdge*> edges = m_widget->getEdges();
    qSort(edges.begin(), edges.end(), GraphEdge::compare);
    foreach (GraphEdge* edge, edges) {
        QString edgeId = EDGE_ID +
                         QString::fromStdString(edge->getSourceNode()->getName()) +
                         EDGE_SEPARATOR +
                         QString::fromStdString(edge->getDestNode()->getName());

        QVariant var = QVariant::fromValue(edge);
        m_objectsList->addItem(edgeId, var);
    }
}

void DeleteObjectDialog::selectObject(int index)
{
    m_selectedObject = m_objectsList->itemData(index);
}

void DeleteObjectDialog::deleteObject()
{
    if (m_selectedObject.canConvert<EmployeeNode*>()) {
        EmployeeNode* emplNode = m_selectedObject.value<EmployeeNode*>();
        deleteNode(emplNode);
    } else if (m_selectedObject.canConvert<SkillNode*>()) {
        SkillNode* skillNode = m_selectedObject.value<SkillNode*>();
        deleteNode(skillNode);

    } else if (m_selectedObject.canConvert<GraphEdge*>()) {
        GraphEdge* edge = m_selectedObject.value<GraphEdge*>();
        deleteEdge(edge);
    }
}

DeleteObjectDialog::~DeleteObjectDialog()
{
}
