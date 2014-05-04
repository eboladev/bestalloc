/*! ---------------------------------------------------------------
 * \file   AddObjectDialog.h
 * \brief  AddObjectDialog class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef ADDOBJECTDIALOG_H_INCLUDED
#define ADDOBJECTDIALOG_H_INCLUDED

#include "EmployeeNode.h"
#include "SkillNode.h"
#include "GraphEdge.h"

#include <QDialog>
#include <QString>
#include <QComboBox>
#include <QList>
#include <QMap>
#include <QRadioButton>

namespace bestalloc
{
    class GraphWidget;

    enum ObjectTypes { EMPLOYEE_NODE, SKILL_NODE, EDGE, PATTERN };

    class AddObjectDialog : public QDialog
    {
        Q_OBJECT

    private:
        GraphWidget* m_widget;

        ObjectTypes m_objectType;

        QString m_nodeName;
        QString m_nodeImageName;
        int     m_edgeWeight;

        QMap<QString, QString> m_employeesMap;
        QMap<QString, QString> m_skillsMap;

        QComboBox*     m_patternsList;
        QComboBox*     m_nodeImageList;
        QLineEdit*     m_weightEdit;

        QComboBox*     m_skillsList;
        QComboBox*     m_employeeList;

        EmployeeNode*  m_selectedEmployeeNode;
        SkillNode*     m_selectedSkillNode;
        QString        m_selectedPatternName;

    public:
        AddObjectDialog(GraphWidget* parent = NULL);
        ~AddObjectDialog();

    signals:
        void enableConfirmButton(bool);
        void enablePatternsList(bool);
        void enableSkillsList(bool);
        void enableEmployeeList(bool);
        void enableImageList(bool);
        void enableWeightEdit(bool);
        void enableLineEdit(bool);
        void addNode(QGraphicsItem*);
        void addEdge(GraphEdge*);
        void updateData(AddObjectDialog*);

    public slots:
        void changeNodeName(const QString& value);
        void changeWeight(const QString& value);

        void setEmployeeObjectType(bool isTrue = true);
        void setSkillObjectType(bool isTrue = true);
        void setPatternObjectType(bool isTrue = true);
        void setEdgeObjectType(bool isTrue = true);

        void selectNodeImage(const QString& imageName);

        void selectPattern(const QString& patternName);
        void selectSkill(int index);
        void selectEmployee(int index);

        void updateContent();

        void confirmNewObject();
    };
}

#endif // ADDOBJECTDIALOG_H_INCLUDED
