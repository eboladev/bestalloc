/*! ---------------------------------------------------------------
 * \file   AddEdgeDialog.h
 * \brief  AddEdgeDialog class declaration
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef ADDEDGEDIALOG_H
#define ADDEDGEDIALOG_H

#include <QDialog>
#include <EmployeeNode.h>
#include <SkillNode.h>
#include <QComboBox>

namespace bestalloc
{
    class AddEdgeDialog : public QDialog
    {
        Q_OBJECT

        QComboBox *m_skillsList;
        QComboBox *m_employeeList;
        QLineEdit* m_weightEdit;

        EmployeeNode *m_selectedEmployeeNode;
        SkillNode *m_selectedSkillNode;
    public:
        AddEdgeDialog(GraphWidget *parent);
        ~AddEdgeDialog();
        void addElement(EmployeeNode *obj);
        void addElement(SkillNode *obj);
    signals:

    public slots:
        void selectSkill(int index);
        void selectEmployee(int index);
        void addEdge();
    };
}

#endif // ADDEDGEDIALOG_H
