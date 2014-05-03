/*! ---------------------------------------------------------------
 * \file   AddObjectDialog.cpp
 * \brief  AddObjectDialog class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "AddObjectDialog.h"
#include "GraphWidget.h"
using namespace bestalloc;

#include "Constants.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QLayout>
#include <QComboBox>
#include <QDebug>
#include <QIntValidator>

AddObjectDialog::AddObjectDialog(GraphWidget *parent)
    : QDialog(parent),
      m_widget(parent),
      m_objectType(EMPLOYEE_NODE),
      m_nodeName(""),
      m_nodeImageName(":/images/staff_admin.png"),
      m_edgeWeight(0),
      m_employeesMap(),
      m_skillsMap(),
      m_selectedEmployeeNode(NULL),
      m_selectedSkillNode(NULL),
      m_selectedPatternName("")
{
    m_employeesMap.insert("Administrator", ":/images/staff_admin.png");
    m_employeesMap.insert("Boss", ":/images/staff_boss.png");
    m_employeesMap.insert("Businessman", ":/images/staff_businessman.png");
    m_employeesMap.insert("Chief", ":/images/staff_chief.png");
    m_employeesMap.insert("Devil", ":/images/staff_devil.png");
    m_employeesMap.insert("Engineer", ":/images/staff_engineer.png");
    m_employeesMap.insert("Female boss", ":/images/staff_female_boss.png");
    m_employeesMap.insert("Global manager", ":/images/staff_global_manager.png");
    m_employeesMap.insert("Manager", ":/images/staff_manager.png");
    m_employeesMap.insert("Old boss", ":/images/staff_old_boss.png");
    m_employeesMap.insert("Professor", ":/images/staff_professor.png");
    m_employeesMap.insert("Security", ":/images/staff_security.png");
    m_employeesMap.insert("Superman", ":/images/staff_superman.png");
    m_employeesMap.insert("Supervisor", ":/images/staff_supervisor.png");
    m_employeesMap.insert("Teacher", ":/images/staff_teacher.png");

    m_skillsMap.insert("HTML", ":/images/res_html.png");
    m_skillsMap.insert("MySQL", ":/images/res_mysql.png");
    m_skillsMap.insert("MS Office", ":/images/res_office.png");
    m_skillsMap.insert("Perl", ":/images/res_perl.png");
    m_skillsMap.insert("Photoshop", ":/images/res_photoshop.png");
    m_skillsMap.insert("PHP", ":/images/res_php.png");
    m_skillsMap.insert("Python", ":/images/res_python.png");
    m_skillsMap.insert("Qt", ":/images/res_qt.png");
    m_skillsMap.insert("Ruby", ":/images/res_ruby.png");
    m_skillsMap.insert("VS 2010", ":/images/res_vs.png");

    QLineEdit* nodeNameLineEdit = new QLineEdit(this);
    nodeNameLineEdit->setMaxLength(MAX_NODE_NAME_LENGTH);
    connect(nodeNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(changeNodeName(QString)));
    connect(this, SIGNAL(enableLineEdit(bool)), nodeNameLineEdit, SLOT(setEnabled(bool)));

    QLabel* nodeNameLabel = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    nodeNameLabel->setBuddy(nodeNameLabel);

    QRadioButton* employeeRadioBtn = new QRadioButton(GRAPH_EMPLOYEE_TYPE_LABEL, this);
    employeeRadioBtn->setChecked(true);
    connect(employeeRadioBtn, SIGNAL(toggled(bool)), SLOT(setEmployeeObjectType(bool)));

    QRadioButton* skillRadioBtn = new QRadioButton(GRAPH_SKILL_TYPE_LABEL, this);
    connect(skillRadioBtn, SIGNAL(toggled(bool)), SLOT(setSkillObjectType(bool)));

    m_nodeImageList = new QComboBox(this);
    connect(m_nodeImageList, SIGNAL(currentIndexChanged(QString)), SLOT(selectNodeImage(QString)));
    connect(this, SIGNAL(enableImageList(bool)), m_nodeImageList, SLOT(setEnabled(bool)));

    QLabel* nodeImageLabel = new QLabel(GRAPH_NODE_IMAGE_LABEL, this);
    nodeImageLabel->setBuddy(m_nodeImageList);

    QRadioButton* patternRadioBtn = new QRadioButton(GRAPH_PATTERN_TYPE_LABEL, this);
    connect(patternRadioBtn, SIGNAL(toggled(bool)), SLOT(setPatternObjectType(bool)));

    QComboBox* patternsList = new QComboBox(this);
    connect(patternsList, SIGNAL(currentIndexChanged(QString)), SLOT(selectPattern(QString)));
    connect(this, SIGNAL(enablePatternsList(bool)), patternsList, SLOT(setEnabled(bool)));
    patternsList->setEnabled(false);

    QMap<QString, QString>::iterator i;
    for (i = m_skillsMap.begin(); i != m_skillsMap.end(); i++) {
        patternsList->addItem(i.key());
    }

    QPushButton* confirmButton = new QPushButton(CONFIRM_LABEL, this);
    connect(confirmButton, SIGNAL(clicked()), SLOT(confirmNewObject()));
    connect(this, SIGNAL(enableConfirmButton(bool)), confirmButton, SLOT(setEnabled(bool)));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QRadioButton* edgeRadioBtn = new QRadioButton(GRAPH_EDGE_TYPE_LABEL, this);
    connect(edgeRadioBtn, SIGNAL(toggled(bool)), SLOT(setEdgeObjectType(bool)));

    m_skillsList = new QComboBox(this);
    connect(m_skillsList, SIGNAL(currentIndexChanged(int)), SLOT(selectSkill(int)));
    connect(this, SIGNAL(enableSkillsList(bool)), m_skillsList, SLOT(setEnabled(bool)));

    m_employeeList = new QComboBox(this);
    connect(m_employeeList, SIGNAL(currentIndexChanged(int)), SLOT(selectEmployee(int)));
    connect(this, SIGNAL(enableEmployeeList(bool)), m_employeeList, SLOT(setEnabled(bool)));

    m_weightEdit = new QLineEdit(this);
    connect(m_weightEdit, SIGNAL(textChanged(QString)), this, SLOT(changeWeight(QString)));
    connect(this, SIGNAL(enableWeightEdit(bool)), m_weightEdit, SLOT(setEnabled(bool)));

    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(0);
    m_weightEdit->setValidator(validator);

    QLabel* weightLabel = new QLabel(GRAPH_NODE_WEIGHT_LABEL, this);
    weightLabel->setBuddy(m_weightEdit);

    QHBoxLayout* nodeNameLayout = new QHBoxLayout;
    nodeNameLayout->addWidget(nodeNameLabel);
    nodeNameLayout->addWidget(nodeNameLineEdit);

    QHBoxLayout* nodeImageLayout = new QHBoxLayout;
    nodeImageLayout->addWidget(nodeImageLabel);
    nodeImageLayout->addWidget(m_nodeImageList);

    QHBoxLayout *nodeWeightLayout = new QHBoxLayout;
    nodeWeightLayout->addWidget(weightLabel);
    nodeWeightLayout->addWidget(m_weightEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(employeeRadioBtn);
    leftLayout->addWidget(skillRadioBtn);
    leftLayout->addLayout(nodeNameLayout);
    leftLayout->addLayout(nodeImageLayout);
    leftLayout->addWidget(edgeRadioBtn);
    leftLayout->addWidget(m_employeeList);
    leftLayout->addWidget(m_skillsList);
    leftLayout->addLayout(nodeWeightLayout);
    leftLayout->addWidget(patternRadioBtn);
    leftLayout->addWidget(patternsList);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addWidget(confirmButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch(1);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(11);
    mainLayout->setSpacing(6);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setWindowTitle(ADD_OBJECT_LABEL);

    setEmployeeObjectType();

    enableConfirmButton(false);
    enablePatternsList(false);
    enableSkillsList(false);
    enableEmployeeList(false);
    enableWeightEdit(false);

    updateData();
}

void AddObjectDialog::changeNodeName(const QString& value)
{
    m_nodeName = value;
    emit(enableConfirmButton(m_nodeName.size() > 0));
}

void AddObjectDialog::changeWeight(const QString& value)
{
    m_edgeWeight = value.toInt();
    emit(enableConfirmButton(m_edgeWeight >= 0 && value != ""));
}

void AddObjectDialog::setEmployeeObjectType(bool isTrue)
{
    m_objectType = EMPLOYEE_NODE;

    m_nodeImageList->clear();
    QMap<QString, QString>::iterator i;
    for (i = m_employeesMap.begin(); i != m_employeesMap.end(); i++) {
        m_nodeImageList->addItem(i.key());
    }

    emit(enableConfirmButton(m_nodeName.size() > 0));
    emit(enableLineEdit(isTrue));
}

void AddObjectDialog::setSkillObjectType(bool isTrue)
{
    m_objectType = SKILL_NODE;

    m_nodeImageList->clear();
    QMap<QString, QString>::iterator i;
    for (i = m_skillsMap.begin(); i != m_skillsMap.end(); i++) {
        m_nodeImageList->addItem(i.key());
    }

    emit(enableConfirmButton(m_nodeName.size() > 0));
    emit(enableLineEdit(isTrue));
}

void AddObjectDialog::setEdgeObjectType(bool isTrue)
{
    m_objectType = EDGE;

    emit(enableConfirmButton(m_weightEdit->text() != ""));
    emit(enableSkillsList(isTrue));
    emit(enableEmployeeList(isTrue));
    emit(enableWeightEdit(isTrue));
}

void AddObjectDialog::setPatternObjectType(bool isTrue)
{
    m_objectType = PATTERN;

    emit(enableConfirmButton(isTrue));
    emit(enablePatternsList(isTrue));
}

void AddObjectDialog::selectNodeImage(const QString& imageName)
{
    switch (m_objectType) {
        case EMPLOYEE_NODE:
            m_nodeImageName = m_employeesMap.value(imageName);
            break;

        case SKILL_NODE:
            m_nodeImageName = m_skillsMap.value(imageName);
            break;

        default:
            break;
    }
}

void AddObjectDialog::selectPattern(const QString& patternName)
{
    m_selectedPatternName = patternName;
}

void AddObjectDialog::selectSkill(int index)
{
    QVariant var = m_skillsList->itemData(index);
    SkillNode* obj = var.value<SkillNode*>();
    m_selectedSkillNode = obj;
}

void AddObjectDialog::selectEmployee(int index)
{
    QVariant var = m_employeeList->itemData(index);
    EmployeeNode* obj = var.value<EmployeeNode*>();
    m_selectedEmployeeNode = obj;
}

void AddObjectDialog::updateData()
{
    if (m_widget == NULL) return;

    m_employeeList->clear();

    QList<EmployeeNode*> employees = m_widget->getEmployeeNodes();
    foreach (EmployeeNode *emplNode, employees) {
        QVariant var = QVariant::fromValue(emplNode);
        m_employeeList->addItem(QString::fromStdString(emplNode->getName()), var);
    }

    m_skillsList->clear();

    QList<SkillNode*> skills = m_widget->getSkillNodes();
    foreach (SkillNode* skillNode, skills) {
        QVariant var = QVariant::fromValue(skillNode);
        m_skillsList->addItem(QString::fromStdString(skillNode->getName()), var);
    }
}

void AddObjectDialog::confirmNewObject()
{
    EmployeeNode* newEmplNode;
    SkillNode* newSkillNode;
    GraphEdge* newEdge;

    switch (m_objectType) {
        case EMPLOYEE_NODE:
            newEmplNode = new EmployeeNode(m_nodeName, QPixmap(m_nodeImageName), m_widget);
            emit(addNode(newEmplNode));
            break;

        case SKILL_NODE:
            newSkillNode = new SkillNode(m_nodeName, QPixmap(m_nodeImageName), m_widget);
            emit(addNode(newSkillNode));
            break;

        case EDGE:
            newEdge = new GraphEdge(m_selectedEmployeeNode, m_selectedSkillNode, m_edgeWeight);
            emit(addEdge(newEdge));
            break;

        case PATTERN:
            newSkillNode = new SkillNode(m_selectedPatternName, m_skillsMap.value(m_selectedPatternName));
            emit(addNode(newSkillNode));
            break;

        default:
            break;
    }
}

AddObjectDialog::~AddObjectDialog()
{
}
