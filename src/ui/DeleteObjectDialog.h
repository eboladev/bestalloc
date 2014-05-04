/*! ---------------------------------------------------------------
 * \file   DeleteObjectDialog.h
 * \brief  DeleteObjectDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef DELETEOBJECTDIALOG_H_INCLUDED
#define DELETEOBJECTDIALOG_H_INCLUDED

#include "EmployeeNode.h"
#include "SkillNode.h"
#include "GraphEdge.h"

#include <QDialog>
#include <QComboBox>

namespace bestalloc
{
    class GraphWidget;

    class DeleteObjectDialog : public QDialog
    {
        Q_OBJECT

    private:
        GraphWidget* m_widget;
        QComboBox*   m_objectsList;
        QVariant     m_selectedObject;

    public:
        DeleteObjectDialog(GraphWidget *parent);
        ~DeleteObjectDialog();

    signals:
        void deleteNode(QGraphicsItem*);
        void deleteEdge(GraphEdge*);

    public slots:
        void updateContent();
        void selectObject(int index);
        void deleteObject();
    };
}

#endif // DELETEOBJECTDIALOG_H_INCLUDED
