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

namespace bestalloc
{
    class AddNodeDialog : public QDialog
    {
        Q_OBJECT

    private:
        QString m_itemName;
        QString m_itemImagePath;
        bool    m_isSkillNode;
        QRadioButton* m_patternRadioBtn;
        QComboBox* m_patternsList;
        QList<QString> m_patternsNames;
        QList<QString> m_patternsImages;
        int m_patternIndex;

    public:
        AddNodeDialog(QWidget* parent = NULL);
        ~AddNodeDialog();

    public slots:
        void changeItemName(const QString& name);
        void setSkillNodeType(bool isTrue);
        void setEmployeeNodeType(bool isTrue);
        void setPatternNodeType(bool isTrue);
        void selectPattern(int index);
        void confirmNewItem();

    signals:
        void enableConfirmButton(bool);
        void enablePatternsList(bool);
        void enableLineEdit(bool);
        void addEmployeeNode(EmployeeNode*);
        void addSkillNode(SkillNode*);
    };
}

#endif // ADDNODEDIALOG_H_INCLUDED
