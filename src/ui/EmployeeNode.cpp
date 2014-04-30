/*! ---------------------------------------------------------------
 * \file   EmployeeNode.cpp
 * \brief  EmployeeNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "EmployeeNode.h"
#include "GraphWidget.h"
#include "ConfigReader.h"
using namespace bestalloc;

#include <QMenu>
#include <QMessageBox>
#include <QGraphicsSceneContextMenuEvent>

static int s_globalEmployeeCounter = 0;

EmployeeNode::EmployeeNode(const QString &name, const QPixmap &nodePicture, GraphWidget* widget)
    : Employee(s_globalEmployeeCounter++, name.toStdString()), GraphNode(nodePicture, widget), TaskObject()
{
}

void EmployeeNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu contextMenu;
    QAction* editAction = contextMenu.addAction(EDIT_MENU_LABEL);
    contextMenu.addAction(DELETE_MENU_LABEL);

    QAction* selectedAction = contextMenu.exec(event->screenPos());
    if (selectedAction != NULL) {
        if (selectedAction == editAction) {

        } else { // Delete
            QMessageBox msgBox;
            msgBox.setWindowTitle(CONFIRM_DELETION_TITLE);
            msgBox.setText(CONFIRM_DELETION_TEXT);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Ok:
                    m_widget->deleteEmployeeNode(this);
                    break;

                case QMessageBox::Cancel:
                    break;

                default:
                    break;
            }
        }
    }
}

void EmployeeNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphNode::paint(painter, option, widget);

    painter->setBrush(Qt::black);
    painter->setFont(QFont("Monospace", 11));

    painter->drawText(QRect(-100, -140, 100, 50), Qt::AlignCenter | Qt::AlignTop, QString(getName().c_str()));
}

/*
void EmployeeNode::save(QDataStream &str)
{
    this->Employee::save(str);
    this->GraphNode::save(str);
}

void EmployeeNode::load(QDataStream &str)
{
    this->Employee::load(str);
    this->GraphNode::load(str);
}
*/

QString EmployeeNode::getTaskName()
{
    return getName().data();
}

void EmployeeNode::printTo(QLineEdit *editName, QLineEdit *editPower)
{
    editName->setEnabled(true);
    editPower->setEnabled(false);
    editName->setText(getName().data());
}

QGraphicsItem *EmployeeNode::getGraphItem()
{
    return new QGraphicsPixmapItem(getPixmap());
    return NULL;
}

void EmployeeNode::setFrom(QLineEdit *editName, QLineEdit *editPower)
{
    string newName = ConfigReader::readString(editName->text());
    setName(newName);
}

void EmployeeNode::setImage(QGraphicsItem *item)
{
    GraphNode::setImage(item);
}

EmployeeNode::~EmployeeNode()
{
}
