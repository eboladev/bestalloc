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

AddNodeDialog::AddNodeDialog(QWidget *parent)
    : QDialog(parent),
      m_itemName(""),
      m_itemImagePath(":images/staff_superman.png"),
      m_isSkillNode(false)
{
    QLineEdit* lineEdit = new QLineEdit(this);
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(changeItemName(QString)));

    QLabel* label = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    label->setBuddy(lineEdit);

    QRadioButton* employeeRadioBtn = new QRadioButton(GRAPH_EMPLOYEE_TYPE_LABEL, this);
    employeeRadioBtn->setChecked(true);
    connect(employeeRadioBtn, SIGNAL(toggled(bool)), SLOT(changeItemType(bool)));

    QRadioButton* skillRadioBtn = new QRadioButton(GRAPH_SKILL_TYPE_LABEL, this);

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
    emit(enableConfirmButton(true));
}

void AddNodeDialog::changeItemType(bool isSkillNode)
{
    m_isSkillNode = isSkillNode;
}

void AddNodeDialog::confirmNewItem()
{

}

AddNodeDialog::~AddNodeDialog()
{
}
