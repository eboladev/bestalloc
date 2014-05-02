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
#include <QComboBox>

namespace bestalloc
{
    class GraphWidget;
    class DeleteObjectDialog : public QDialog
    {
        Q_OBJECT

    private:
        QComboBox*  m_objectsList;
        //TaskObject* m_selectedObject;
        int         m_selectedIndex;

    public:
        DeleteObjectDialog(GraphWidget *parent);
        //void addElement(TaskObject *obj);
        ~DeleteObjectDialog();

    public slots:
        void selectObject(int index);
        void deleteObject();
    };
}
#endif // DELETEOBJECTDIALOG_H
