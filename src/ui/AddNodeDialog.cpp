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

AddNodeDialog::AddNodeDialog(QWidget *parent)
    : QDialog(parent),
      m_itemName(""),
      m_itemImagePath(":images/staff_superman.png"),
      m_isSkillNode(false)
{
    m_patternsNames.append("PHP");
    m_patternsImages.append(":images/res_php.png");
    m_patternsNames.append("Perl");
    m_patternsImages.append(":images/res_perl.png");
    m_patternsNames.append("Qt");
    m_patternsImages.append(":images/res_qt.png");

    QLineEdit* lineEdit = new QLineEdit(this);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changeItemName(QString)));
    connect(this, SIGNAL(enableLineEdit(bool)), lineEdit, SLOT(setEnabled(bool)));

    QLabel* label = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    label->setBuddy(lineEdit);

    QRadioButton* employeeRadioBtn = new QRadioButton(GRAPH_EMPLOYEE_TYPE_LABEL, this);
    employeeRadioBtn->setChecked(true);
    connect(employeeRadioBtn, SIGNAL(toggled(bool)), SLOT(setEmployeeNodeType(bool)));

    QRadioButton* skillRadioBtn = new QRadioButton(GRAPH_SKILL_TYPE_LABEL, this);
    connect(skillRadioBtn, SIGNAL(toggled(bool)), SLOT(setSkillNodeType(bool)));

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

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(employeeRadioBtn);
    leftLayout->addWidget(skillRadioBtn);
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
}

void AddNodeDialog::changeItemName(const QString &name)
{
    m_itemName = name;
    emit(enableConfirmButton(m_itemName.size()>0));
}

void AddNodeDialog::setSkillNodeType(bool isTrue)
{
    m_isSkillNode = isTrue;
    emit(enableConfirmButton(m_itemName.size()>0));
}

void AddNodeDialog::setEmployeeNodeType(bool isTrue)
{
    m_isSkillNode = !isTrue;
    emit(enableConfirmButton(m_itemName.size()>0));
}

void AddNodeDialog::setPatternNodeType(bool isTrue)
{
    emit(enablePatternsList(isTrue));
    emit(enableConfirmButton(isTrue));
    emit(enableLineEdit(!isTrue));
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
    }else if (m_isSkillNode) {
        SkillNode* newItem = new SkillNode(m_itemName, QPixmap(":/images/res_photoshop.png"));
        emit(addSkillNode(newItem));
    } else {
        EmployeeNode* newItem = new EmployeeNode(m_itemName, QPixmap(":/images/staff_superman.png"));
        emit(addEmployeeNode(newItem));
    }
}

AddNodeDialog::~AddNodeDialog()
{
}
