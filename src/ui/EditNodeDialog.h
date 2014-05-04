/*! ---------------------------------------------------------------
 * \file   EditNodeDialog.h
 * \brief  EditNodeDialog class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef EDITNODEDIALOG_H
#define EDITNODEDIALOG_H

#include <QDialog>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QLineEdit>

namespace bestalloc
{
    class GraphWidget;

    enum NodeTypes { EMPLOYEE_TYPE, SKILL_TYPE };

    class EditNodeDialog : public QDialog
    {
        Q_OBJECT

    private:
        GraphWidget*         m_widget;

        NodeTypes            m_nodeType;
        int                  m_nodeId;
        QString              m_nodeName;
        QGraphicsPixmapItem* m_nodeImage;

        QLineEdit*           m_nameEdit;
        QGraphicsView*       m_graphicsView;

    public:
        EditNodeDialog(NodeTypes nodeType, int nodeId, GraphWidget* parent = NULL);
        ~EditNodeDialog();

    signals:
        void enableEdition(bool);
        void enableConfirmButton(bool);
        void objectChanged();

    public slots:
        void updateContent();
        void changeNodeName(const QString& value);
        void openPicture();
        void confirmChanges();
    };
}

#endif // EDITNODEDIALOG_H
