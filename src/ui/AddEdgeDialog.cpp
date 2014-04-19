/*! ---------------------------------------------------------------
 * \file   AddEdgeDialog.cpp
 * \brief  AddEdgeDialog class implementaion
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "AddEdgeDialog.h"
using namespace bestalloc;

#include "Constants.h"
#include "GraphWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QLayout>
#include <QComboBox>
#include <QDebug>
#include <QGraphicsView>
#include <QFileDialog>

AddEdgeDialog::AddEdgeDialog(GraphWidget *parent) :
    m_selectedEmployeeNode(0),m_selectedSkillNode(0),QDialog(parent)
{
    m_skillsList = new QComboBox(this);
    connect(m_skillsList, SIGNAL(currentIndexChanged(int)), SLOT(selectSkill(int)));

    m_employeeList = new QComboBox(this);
    connect(m_employeeList, SIGNAL(currentIndexChanged(int)), SLOT(selectEmployee(int)));

    QPushButton * confirmButton = new QPushButton(CONFIRM_LABEL, this);
    confirmButton->setDefault(true);
    connect(confirmButton, SIGNAL(clicked()), SLOT(addEdge()));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layoutBtns = new QHBoxLayout;
    layoutBtns->addWidget(confirmButton);
    layoutBtns->addWidget(closeButton);

    m_weightEdit = new QLineEdit(this);

    QLabel* label = new QLabel(GRAPH_NODE_POWER_LABEL, this);
    label->setBuddy(m_weightEdit);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(m_weightEdit);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(m_skillsList);
    rightLayout->addWidget(m_employeeList);
    rightLayout->addLayout(topLeftLayout);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(ADD_EDGE_LABEL);
}

AddEdgeDialog::~AddEdgeDialog()
{
}

void AddEdgeDialog::addElement(EmployeeNode *obj)
{
    QVariant v = QVariant::fromValue(obj);
    m_employeeList->addItem(obj->getTaskName(),v);
}

void AddEdgeDialog::addElement(SkillNode *obj)
{
    QVariant v = QVariant::fromValue(obj);
    m_skillsList->addItem(obj->getTaskName(),v);
}

void AddEdgeDialog::selectSkill(int index)
{
    QVariant v = m_skillsList->itemData(index);
    SkillNode *obj = v.value<SkillNode*>();
    m_selectedSkillNode = obj;
}

void AddEdgeDialog::selectEmployee(int index)
{
    QVariant v = m_employeeList->itemData(index);
    EmployeeNode *obj = v.value<EmployeeNode*>();
    m_selectedEmployeeNode = obj;
}

void AddEdgeDialog::addEdge()
{
    if(m_selectedEmployeeNode && m_selectedSkillNode){
        int weight = m_weightEdit->text().toInt();
        GraphEdge* edge = new GraphEdge(m_selectedEmployeeNode, m_selectedSkillNode, weight);
        ((GraphWidget *)parentWidget())->addEdge(edge);
    }
}
