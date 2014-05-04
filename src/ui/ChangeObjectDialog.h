/*! ---------------------------------------------------------------
 * \file   ChangeObjectDialog.h
 * \brief  ChangeObjectDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CHANGEOBJECTDIALOG_H_INCLUDED
#define CHANGEOBJECTDIALOG_H_INCLUDED

#include <QDialog>
#include <QComboBox>
#include <QVariant>
#include <QGraphicsView>

namespace bestalloc
{
    class EmployeeNode;
    class SkillNode;
    class GraphEdge;
    class GraphWidget;

    class ChangeObjectDialog : public QDialog
    {
        Q_OBJECT

    private:
        GraphWidget* m_widget;

        QVariant     m_selectedObject;
        QVariant     m_lastChangedObject;
        QComboBox*   m_objectsList;

        QGraphicsPixmapItem* m_nodeImage;

        QLineEdit*           m_nameEdit;
        QLineEdit*           m_weightEdit;
        QGraphicsView*       m_graphicsView;

    public:
        ChangeObjectDialog(GraphWidget* parent = NULL);
        ~ChangeObjectDialog();

    signals:
        void enableNodeEdit(bool);
        void enableEdgeEdit(bool);
        void enableConfirmButton(bool);
        void objectChanged();

    public slots:
        void updateContent();
        void changeNodeName(const QString& value);
        void changeWeight(const QString& value);
        void selectObject(int index);
        void openPicture();
        void confirmChanges();

        void restoreSelection();
        void restoreEmployeeNode(EmployeeNode*);
        void restoreSkillNode(SkillNode*);
        void restoreEdge(GraphEdge* edge);
    };
}

#endif // CHANGEOBJECTDIALOG_H_INCLUDED
