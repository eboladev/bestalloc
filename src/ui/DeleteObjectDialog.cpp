/*! ---------------------------------------------------------------
 * \file   DeleteObjectDialog.cpp
 * \brief  DeleteObjectDialog class implementation
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "DeleteObjectDialog.h"
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
#include <QMessageBox>

DeleteObjectDialog::DeleteObjectDialog(GraphWidget *parent)
    : QDialog(parent), m_selectedIndex(0), m_selectedObject(NULL)
{
    m_objectsList = new QComboBox(this);
    connect(m_objectsList, SIGNAL(currentIndexChanged(int)), SLOT(selectObject(int)));

    QPushButton * confirmButton = new QPushButton(DELETE_LABEL, this);
    confirmButton->setDefault(true);
    connect(confirmButton, SIGNAL(clicked()), SLOT(deleteObject()));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layoutBtns = new QHBoxLayout;
    layoutBtns->addWidget(confirmButton);
    layoutBtns->addWidget(closeButton);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(m_objectsList);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(DELETE_OBJECT_LABEL);
}

void DeleteObjectDialog::addElement(TaskObject *obj)
{
    QVariant v = QVariant::fromValue(obj);
    m_objectsList->addItem(obj->getTaskName(),v);
}

void DeleteObjectDialog::selectObject(int index)
{
    QVariant v = m_objectsList->itemData(index);
    TaskObject *obj = v.value<TaskObject*>();
    m_selectedObject = obj;
    m_selectedIndex = index;
}

void DeleteObjectDialog::deleteObject()
{
    if (m_selectedObject) {
        if (((GraphWidget *)parentWidget())->deleteObject(m_selectedObject)) {
            m_objectsList->removeItem(m_selectedIndex);
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Warning");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Can`t delete object.");
            msgBox.setInformativeText("Object has edges or not found.");
            msgBox.exec();
        }
    }
}

DeleteObjectDialog::~DeleteObjectDialog()
{
}
