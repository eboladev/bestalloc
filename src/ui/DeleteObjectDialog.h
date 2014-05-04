/*! ---------------------------------------------------------------
 * \file   DeleteObjectDialog.h
 * \brief  DeleteObjectDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef DELETEOBJECTDIALOG_H_INCLUDED
#define DELETEOBJECTDIALOG_H_INCLUDED

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
#endif // DELETEOBJECTDIALOG_H_INCLUDED
