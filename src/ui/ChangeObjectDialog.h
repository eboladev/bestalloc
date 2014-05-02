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
#include <QComboBox>
#include <QGraphicsWidget>

namespace bestalloc
{
    class ChangeObjectDialog : public QDialog
    {
        Q_OBJECT

    private:
        QComboBox *m_objectsList;
        QGraphicsScene* m_scene;
        QLineEdit* m_editName;
        QLineEdit* m_editPower;
        QGraphicsPixmapItem *m_currentImage;
        //TaskObject *m_selectedObject;
        QPushButton *m_openPictureBtn;
    public:
        ChangeObjectDialog(QWidget* parent = NULL);
        ~ChangeObjectDialog();
        //void addElement(TaskObject *obj);

    public slots:
        void selectObject(int index);
        void confirmChanges();
        void openPicture();

    signals:
        void updateImage();
    };
}
#endif // CHANGEOBJECTDIALOG_H
