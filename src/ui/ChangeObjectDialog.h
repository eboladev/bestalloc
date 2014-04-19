/*! ---------------------------------------------------------------
 * \file   ChangeObjectDialog.h
 * \brief  ChangeObjectDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CHANGEOBJECTDIALOG_H
#define CHANGEOBJECTDIALOG_H

#include <QDialog>
#include "TaskObject.h"
#include <QComboBox>

namespace bestalloc
{
    class ChangeObjectDialog : public QDialog
    {
        Q_OBJECT

        QComboBox *m_objectsList;
        QGraphicsScene* m_scene;
        QLineEdit* m_editName;
        QLineEdit* m_editPower;
        QGraphicsItem *m_currentImage;
        TaskObject *m_selectedObject;
        QPushButton *m_openPictureBtn;
    public:
        ChangeObjectDialog(QWidget* parent = NULL);
        ~ChangeObjectDialog();
        void addElement(TaskObject *obj);


    public slots:
        void selectObject(int index);
        void confirmChanges();
        void openPicture();
    signals:

    };
}
#endif // CHANGEOBJECTDIALOG_H