/*! ---------------------------------------------------------------
 * \file   DeleteObjectDialog.h
 * \brief  DeleteObjectDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef DELETEOBJECTDIALOG_H
#define DELETEOBJECTDIALOG_H

#include <QDialog>
#include "TaskObject.h"
#include <QComboBox>

namespace bestalloc
{
    class GraphWidget;
    class DeleteObjectDialog : public QDialog
    {
        Q_OBJECT

        QComboBox *m_objectsList;
        TaskObject *m_selectedObject;
        int m_selectedIndex;
    public:
        DeleteObjectDialog(GraphWidget *parent);
        ~DeleteObjectDialog();
        void addElement(TaskObject *obj);
    public slots:
        void selectObject(int index);
        void deleteObject();
    signals:

    };
}
#endif // DELETEOBJECTDIALOG_H
