/*! ---------------------------------------------------------------
 * \file   AddNodeDialog.cpp
 * \brief  AddNodeDialog class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "AddNodeDialog.h"
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

#define ADD_PATTERN(name,image)\
    m_patternsNames.append(#name);\
    m_patternsImages.append(":images/"#image".png");

AddNodeDialog::AddNodeDialog(QWidget *parent)
    : m_selectedEmployeeNode(0),
      m_selectedSkillNode(0),
      QDialog(parent),
      m_weight(0),
      m_itemName("")
{
    ADD_PATTERN(PHP,res_php);
    ADD_PATTERN(Perl,res_perl);
    ADD_PATTERN(Qt,res_qt);
    ADD_PATTERN(HTML,res_html);
    ADD_PATTERN(MySQL,res_mysql);
    ADD_PATTERN(Office,res_office);
    ADD_PATTERN(Photoshop,res_photoshop);
    ADD_PATTERN(Python,res_python);
    ADD_PATTERN(Ruby,res_ruby);
    ADD_PATTERN(VS,res_vs);

    QLineEdit* lineEdit = new QLineEdit(this);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changeItemName(QString)));
    connect(this, SIGNAL(enableLineEdit(bool)), lineEdit, SLOT(setEnabled(bool)));

    QLabel* label = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    label->setBuddy(lineEdit);

    m_employeeRadioBtn = new QRadioButton(GRAPH_EMPLOYEE_TYPE_LABEL, this);
    m_employeeRadioBtn->setChecked(true);
    connect(m_employeeRadioBtn, SIGNAL(toggled(bool)), SLOT(setEmployeeNodeType(bool)));

    m_skillRadioBtn = new QRadioButton(GRAPH_SKILL_TYPE_LABEL, this);
    connect(m_skillRadioBtn, SIGNAL(toggled(bool)), SLOT(setSkillNodeType(bool)));

    m_patternRadioBtn = new QRadioButton(GRAPH_PATTERN_TYPE_LABEL, this);
    connect(m_patternRadioBtn, SIGNAL(toggled(bool)), SLOT(setPatternNodeType(bool)));

    QComboBox *patternsList = new QComboBox(this);
    connect(patternsList, SIGNAL(currentIndexChanged(int)), SLOT(selectPattern(int)));
    connect(this, SIGNAL(enablePatternsList(bool)), patternsList, SLOT(setEnabled(bool)));
    patternsList->setEnabled(false);
    foreach (QString cur, m_patternsNames) {
        patternsList->addItem(cur);
    }

    QPushButton* confirmButton = new QPushButton(CONFIRM_LABEL, this);
    confirmButton->setDefault(true);
    confirmButton->setEnabled(false);
    connect(confirmButton, SIGNAL(clicked()), SLOT(confirmNewItem()));
    connect(this, SIGNAL(enableConfirmButton(bool)), confirmButton, SLOT(setEnabled(bool)));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    m_edgeRadioBtn = new QRadioButton(GRAPH_EDGE_TYPE_LABEL, this);
    connect(m_edgeRadioBtn, SIGNAL(toggled(bool)), SLOT(setEdgeNodeType(bool)));

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

    QLabel* weightLabel = new QLabel(GRAPH_NODE_POWER_LABEL, this);
    weightLabel->setBuddy(m_weightEdit);

    QHBoxLayout *botLeftLayout = new QHBoxLayout;
    botLeftLayout->addWidget(weightLabel);
    botLeftLayout->addWidget(m_weightEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_employeeRadioBtn);
    leftLayout->addWidget(m_skillRadioBtn);
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(m_edgeRadioBtn);
    leftLayout->addWidget(m_skillsList);
    leftLayout->addWidget(m_employeeList);
    leftLayout->addLayout(botLeftLayout);
    leftLayout->addWidget(m_patternRadioBtn);
    leftLayout->addWidget(patternsList);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(confirmButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch(1);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(11);
    mainLayout->setSpacing(6);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setWindowTitle(ADD_NODE_LABEL);

    enableConfirmButton(false);
    enablePatternsList(false);
    enableSkillsList(false);
    enableEmployeeList(false);
    enableWeightEdit(false);
}

void AddNodeDialog::changeItemName(const QString &name)
{
    m_itemName = name;
    emit(enableConfirmButton(m_itemName.size()>0));
}

void AddNodeDialog::changeWeight(const QString &weight)
{
    m_weight = weight.toInt();
    emit(enableConfirmButton(m_weight>=0));
}

void AddNodeDialog::setSkillNodeType(bool isTrue)
{
    emit(enableConfirmButton(m_itemName.size()>0));
    emit(enableLineEdit(isTrue));
}

void AddNodeDialog::setEmployeeNodeType(bool isTrue)
{
    emit(enableConfirmButton(m_itemName.size()>0));
    emit(enableLineEdit(isTrue));
}

void AddNodeDialog::setPatternNodeType(bool isTrue)
{
    emit(enableConfirmButton(isTrue));
    emit(enablePatternsList(isTrue));
}

void AddNodeDialog::setEdgeNodeType(bool isTrue)
{
    emit(enableConfirmButton(m_weight>=0));
    emit(enableSkillsList(isTrue));
    emit(enableEmployeeList(isTrue));
    emit(enableWeightEdit(isTrue));
}

void AddNodeDialog::selectPattern(int index)
{
    m_patternIndex = index;
}

void AddNodeDialog::confirmNewItem()
{
    if(m_patternRadioBtn->isChecked()){
        SkillNode* newItem = new SkillNode(m_patternsNames.at(m_patternIndex), QPixmap(m_patternsImages.at(m_patternIndex)));
        emit(addSkillNode(newItem));
    }else if(m_edgeRadioBtn->isChecked()){
        if(m_selectedEmployeeNode && m_selectedSkillNode){
            GraphEdge* edge = new GraphEdge(m_selectedEmployeeNode, m_selectedSkillNode, m_weight);
            emit(addEdge(edge));
        }
    }else if (m_skillRadioBtn->isChecked()) {
        SkillNode* newItem = new SkillNode(m_itemName, QPixmap(":/images/res_photoshop.png"));
        emit(addSkillNode(newItem));
    } else if (m_employeeRadioBtn->isChecked()){
        EmployeeNode* newItem = new EmployeeNode(m_itemName, QPixmap(":/images/staff_superman.png"));
        emit(addEmployeeNode(newItem));
    }
    emit(updateData(this));
}

void AddNodeDialog::selectSkill(int index)
{
    /*QVariant v = m_skillsList->itemData(index);
    SkillNode *obj = v.value<SkillNode*>();
    m_selectedSkillNode = obj;*/
}

void AddNodeDialog::selectEmployee(int index)
{
/*    QVariant v = m_employeeList->itemData(index);
    EmployeeNode *obj = v.value<EmployeeNode*>();
    m_selectedEmployeeNode = obj;*/
}

void AddNodeDialog::updateData(QList<EmployeeNode *> &employees, QList<SkillNode *> &skills)
{
/*    m_employeeList->clear();
    foreach (EmployeeNode *cur, employees) {
        QVariant v = QVariant::fromValue(cur);
        m_employeeList->addItem(cur->getTaskName(),v);
    }

    m_skillsList->clear();
    foreach (SkillNode *cur, skills) {
        QVariant v = QVariant::fromValue(cur);
        m_skillsList->addItem(cur->getTaskName(),v);
    }*/
}

AddNodeDialog::~AddNodeDialog()
{
}
