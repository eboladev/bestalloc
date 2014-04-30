/*! ---------------------------------------------------------------
 * \file   AddNodeDialog.h
 * \brief  AddNodeDialog class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef ADDNODEDIALOG_H_INCLUDED
#define ADDNODEDIALOG_H_INCLUDED

#include <QDialog>
#include <QString>
#include <QComboBox>
#include <QList>
#include <QRadioButton>

#include "EmployeeNode.h"
#include "SkillNode.h"
#include "GraphEdge.h"

namespace bestalloc
{
    class AddNodeDialog : public QDialog
    {
        Q_OBJECT

    private:
        QString m_itemName;

        QRadioButton*  m_employeeRadioBtn;
        QRadioButton*  m_skillRadioBtn;

        QRadioButton*  m_patternRadioBtn;
        QComboBox*     m_patternsList;
        QList<QString> m_patternsNames;
        QList<QString> m_patternsImages;
        int            m_patternIndex;

        QRadioButton*  m_edgeRadioBtn;
        QComboBox*     m_skillsList;
        QComboBox*     m_employeeList;
        QLineEdit*     m_weightEdit;

        int            m_weight;
        EmployeeNode*  m_selectedEmployeeNode;
        SkillNode*     m_selectedSkillNode;

    public:
        AddNodeDialog(QWidget* parent = NULL);
        ~AddNodeDialog();

    public slots:
        void changeItemName(const QString& name);
        void changeWeight(const QString& weight);
        void setSkillNodeType(bool isTrue);
        void setEmployeeNodeType(bool isTrue);
        void setPatternNodeType(bool isTrue);
        void setEdgeNodeType(bool isTrue);
        void selectPattern(int index);
        void confirmNewItem();
        void selectSkill(int index);
        void selectEmployee(int index);
        void updateData(QList<EmployeeNode*> &employees,QList<SkillNode*> &skills);

    signals:
        void enableConfirmButton(bool);
        void enablePatternsList(bool);
        void enableSkillsList(bool);
        void enableEmployeeList(bool);
        void enableWeightEdit(bool);
        void enableLineEdit(bool);
        void addEmployeeNode(EmployeeNode*);
        void addSkillNode(SkillNode*);
        void addEdge(GraphEdge*);
        void updateData(AddNodeDialog*);
    };
}

#endif // ADDNODEDIALOG_H_INCLUDED
