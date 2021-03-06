/*! ---------------------------------------------------------------
 * \file   SkillNode.cpp
 * \brief  SkillNode class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "SkillNode.h"
#include "GraphWidget.h"
#include "EditNodeDialog.h"
#include "Constants.h"
using namespace bestalloc;

#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QMessageBox>
#include <QAction>

static int s_globalSkillCounter = 0;

SkillNode::SkillNode(const QString &name, const QPixmap &nodePicture, GraphWidget* widget)
    : Skill(s_globalSkillCounter++, name.toStdString()), GraphNode(nodePicture, widget)
{
}

void SkillNode::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    if (m_widget == NULL) return;

    QMenu contextMenu;
    QAction* changeAction = contextMenu.addAction(CHANGE_MENU_LABEL);
    contextMenu.addAction(DELETE_MENU_LABEL);

    QAction* selectedAction = contextMenu.exec(event->screenPos());
    if (selectedAction != NULL) {
        if (selectedAction == changeAction) {
            EditNodeDialog* dialog = new EditNodeDialog(SKILL_TYPE, getId(), m_widget);
            QObject::connect(dialog, SIGNAL(objectChanged()), m_widget, SLOT(update()));
            QObject::connect(m_widget, SIGNAL(contentChanged()), dialog, SLOT(updateContent()));
            dialog->show();
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle(CONFIRM_DELETION_TITLE);
            msgBox.setText(CONFIRM_SKILL_DELETION_TEXT + QString("'") + QString::fromStdString(getName()) + QString("'?"));
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);
            int ret = msgBox.exec();
            switch (ret) {
                case QMessageBox::Ok:
                    m_widget->deleteNode(this);
                    break;

                case QMessageBox::Cancel:
                    break;

                default:
                    break;
            }
        }
    }
}

void SkillNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphNode::paint(painter, option, widget);

    painter->setBrush(Qt::black);
    painter->setFont(QFont("Monospace", 11));

    painter->drawText(QRect(-100, -140, 100, 50), Qt::AlignCenter | Qt::AlignTop, QString(getName().c_str()));
}

bool SkillNode::compare(SkillNode* first, SkillNode* second)
{
    if (first == NULL || second == NULL) return false;

    QString firstName = QString::fromStdString(first->getName());
    QString secondName = QString::fromStdString(second->getName());

    if (firstName.compare(secondName, Qt::CaseSensitive) >= 0) {
        return false;
    } else {
        return true;
    }
}

SkillNode::~SkillNode()
{
}
