/*! ---------------------------------------------------------------
 * \file   ChangeObjectDialog.cpp
 * \brief  ChangeObjectDialog class implementation
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "ChangeObjectDialog.h"
#include "GraphWidget.h"
using namespace bestalloc;

#include "Constants.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QLayout>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsView>
#include <QFileDialog>
#include <QIntValidator>
#include <QStyleFactory>
#include <QtAlgorithms>

ChangeObjectDialog::ChangeObjectDialog(GraphWidget* parent)
    : QDialog(parent),
      m_widget(parent),
      m_nodeImage(NULL)
{
    m_objectsList = new QComboBox(this);
    m_objectsList->setStyle(QStyleFactory::create("Windows"));
    connect(m_objectsList, SIGNAL(currentIndexChanged(int)), SLOT(selectObject(int)));

    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setMaxLength(MAX_NODE_NAME_LENGTH);
    connect(m_nameEdit, SIGNAL(textChanged(QString)), this, SLOT(changeNodeName(QString)));
    connect(this, SIGNAL(enableNodeEdit(bool)), m_nameEdit, SLOT(setEnabled(bool)));

    QLabel* nameLabel = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    nameLabel->setBuddy(m_nameEdit);
    connect(this, SIGNAL(enableNodeEdit(bool)), nameLabel, SLOT(setEnabled(bool)));

    QLabel* labelImg = new QLabel(GRAPH_NODE_IMAGE_LABEL, this);
    connect(this, SIGNAL(enableNodeEdit(bool)), labelImg, SLOT(setEnabled(bool)));

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, IMAGE_PREVIEW_SIZE, IMAGE_PREVIEW_SIZE);

    m_graphicsView = new QGraphicsView(this);
    m_graphicsView->setScene(scene);
    m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    connect(this, SIGNAL(enableNodeEdit(bool)), m_graphicsView, SLOT(setEnabled(bool)));

    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(0);

    m_weightEdit = new QLineEdit(this);
    m_weightEdit->setValidator(validator);
    connect(this, SIGNAL(enableEdgeEdit(bool)), m_weightEdit, SLOT(setEnabled(bool)));
    connect(m_weightEdit, SIGNAL(textChanged(QString)), this, SLOT(changeNodeName(QString)));

    QLabel* weightLabel = new QLabel(GRAPH_NODE_WEIGHT_LABEL, this);
    weightLabel->setBuddy(m_weightEdit);
    connect(this, SIGNAL(enableEdgeEdit(bool)), weightLabel, SLOT(setEnabled(bool)));

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(m_nameEdit);

    QPushButton* openPictureBtn = new QPushButton(SELECT_PICTURE_LABEL, this);
    connect(openPictureBtn, SIGNAL(clicked()), SLOT(openPicture()));
    connect(this, SIGNAL(enableNodeEdit(bool)), openPictureBtn, SLOT(setEnabled(bool)));

    QHBoxLayout* layoutImg = new QHBoxLayout;
    layoutImg->addWidget(labelImg);
    layoutImg->addWidget(openPictureBtn);

    QHBoxLayout* layoutPower = new QHBoxLayout;
    layoutPower->addWidget(weightLabel);
    layoutPower->addWidget(m_weightEdit);

    QPushButton* confirmButton = new QPushButton(CONFIRM_LABEL, this);
    connect(confirmButton, SIGNAL(clicked()), SLOT(confirmChanges()));
    connect(this, SIGNAL(enableConfirmButton(bool)), confirmButton, SLOT(setEnabled(bool)));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    closeButton->setDefault(true);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layoutBtns = new QHBoxLayout;
    layoutBtns->addWidget(confirmButton);
    layoutBtns->addWidget(closeButton);

    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(m_objectsList);
    rightLayout->addLayout(nameLayout);
    rightLayout->addWidget(m_graphicsView);
    rightLayout->addLayout(layoutImg);
    rightLayout->addLayout(layoutPower);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(CHANGE_OBJECT_LABEL);

    updateContent();
}

void ChangeObjectDialog::updateContent()
{
    m_objectsList->clear();

    QList<EmployeeNode*> employees = m_widget->getEmployeeNodes();
    qSort(employees.begin(), employees.end(), EmployeeNode::compare);
    foreach (EmployeeNode* emplNode, employees) {
        QVariant var = QVariant::fromValue(emplNode);
        m_objectsList->addItem(EMPLOYEE_ID + QString::fromStdString(emplNode->getName()), var);
    }

    QList<SkillNode*> skills = m_widget->getSkillNodes();
    qSort(skills.begin(), skills.end(), SkillNode::compare);
    foreach (SkillNode* skillNode, skills) {
        QVariant var = QVariant::fromValue(skillNode);
        m_objectsList->addItem(SKILL_ID + QString::fromStdString(skillNode->getName()), var);
    }

    QList<GraphEdge*> edges = m_widget->getEdges();
    qSort(edges.begin(), edges.end(), GraphEdge::compare);
    foreach (GraphEdge* edge, edges) {
        QString edgeId = EDGE_ID +
                         QString::fromStdString(edge->getSourceNode()->getName()) +
                         EDGE_SEPARATOR +
                         QString::fromStdString(edge->getDestNode()->getName());

        QVariant var = QVariant::fromValue(edge);
        m_objectsList->addItem(edgeId, var);
    }
}

void ChangeObjectDialog::changeNodeName(const QString& value)
{
    QString nodeName = "";
    if (m_selectedObject.canConvert<EmployeeNode*>()) {
        EmployeeNode* emplNode = m_selectedObject.value<EmployeeNode*>();
        nodeName = QString::fromStdString(emplNode->getName());
    } else if (m_selectedObject.canConvert<SkillNode*>()) {
        SkillNode* skillNode = m_selectedObject.value<SkillNode*>();
        nodeName = QString::fromStdString(skillNode->getName());
    }

    emit(enableConfirmButton(nodeName != value && value != ""));
}

void ChangeObjectDialog::changeWeight(const QString& value)
{
    emit(enableConfirmButton(value != ""));
}

void ChangeObjectDialog::selectObject(int index)
{
    m_graphicsView->scene()->clear();

    m_selectedObject = m_objectsList->itemData(index);
    if (m_selectedObject.canConvert<EmployeeNode*>()) {
        EmployeeNode* emplNode = m_selectedObject.value<EmployeeNode*>();

        m_nodeImage = new QGraphicsPixmapItem(emplNode->getNodePicture()
                                              .scaledToHeight(IMAGE_PREVIEW_SIZE)
                                              .scaledToWidth(IMAGE_PREVIEW_SIZE));
        m_graphicsView->scene()->addItem(m_nodeImage);

        m_nameEdit->setText(QString::fromStdString(emplNode->getName()));
        m_weightEdit->setText("");

        emit enableNodeEdit(true);
        emit enableEdgeEdit(false);

    } else if (m_selectedObject.canConvert<SkillNode*>()) {
        SkillNode* skillNode = m_selectedObject.value<SkillNode*>();
        m_nodeImage = new QGraphicsPixmapItem(skillNode->getNodePicture()
                                              .scaledToHeight(IMAGE_PREVIEW_SIZE)
                                              .scaledToWidth(IMAGE_PREVIEW_SIZE));
        m_graphicsView->scene()->addItem(m_nodeImage);

        m_nameEdit->setText(QString::fromStdString(skillNode->getName()));
        m_weightEdit->setText("");

        emit enableNodeEdit(true);
        emit enableEdgeEdit(false);

    } else if (m_selectedObject.canConvert<GraphEdge*>()) {
        GraphEdge* edge = m_selectedObject.value<GraphEdge*>();

        m_nameEdit->setText("");
        m_weightEdit->setText(QString::number(edge->getWeight()));

        emit enableNodeEdit(false);
        emit enableEdgeEdit(true);
    }
}

void ChangeObjectDialog::openPicture()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select picture file"), ":/images", tr("png (*.png);;jpeg (*.jpg)"));
    if (fileName != "") {
        QPixmap picture(fileName);
        if (!picture.isNull()) {
            m_graphicsView->scene()->clear();

            m_nodeImage = new QGraphicsPixmapItem(picture.scaledToHeight(IMAGE_PREVIEW_SIZE).scaledToWidth(IMAGE_PREVIEW_SIZE));
            m_graphicsView->scene()->addItem(m_nodeImage);

            emit enableConfirmButton(true);
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle(WARNING_TITLE);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(OPEN_FILE_ERROR_TEXT);
            msgBox.setInformativeText(OPEN_FILE_ERROR_INFO);
            msgBox.exec();
        }
    }
}

void ChangeObjectDialog::confirmChanges()
{
    if (m_widget == NULL) return;

    if (m_selectedObject.canConvert<EmployeeNode*>()) {
        EmployeeNode* emplNode = m_selectedObject.value<EmployeeNode*>();
        string nodeName = m_nameEdit->text().toStdString();

        QList<EmployeeNode*> employees = m_widget->getEmployeeNodes();
        foreach (EmployeeNode* node, employees) {
            if (node->getName() == nodeName && node->getId() != emplNode->getId()) {
                QMessageBox msgBox;
                msgBox.setWindowTitle(WARNING_TITLE);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText(EDIT_EMPLOYEE_ERROR_TEXT);
                msgBox.setInformativeText(EDIT_EMPLOYEE_ERROR_INFO);
                msgBox.exec();

                return;
            }
        }

        emplNode->setName(nodeName);
        emplNode->setNodePicture(m_nodeImage->pixmap());

    } else if (m_selectedObject.canConvert<SkillNode*>()) {
        SkillNode* skillNode = m_selectedObject.value<SkillNode*>();
        string nodeName = m_nameEdit->text().toStdString();

        QList<SkillNode*> skills = m_widget->getSkillNodes();
        foreach (SkillNode* node, skills) {
            if (node->getName() == nodeName && node->getId() != skillNode->getId()) {
                QMessageBox msgBox;
                msgBox.setWindowTitle(WARNING_TITLE);
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText(EDIT_SKILL_ERROR_TEXT);
                msgBox.setInformativeText(EDIT_SKILL_ERROR_INFO);
                msgBox.exec();

                return;
            }
        }

        skillNode->setName(nodeName);
        skillNode->setNodePicture(m_nodeImage->pixmap());

    } else if (m_selectedObject.canConvert<GraphEdge*>()) {
        GraphEdge* edge = m_selectedObject.value<GraphEdge*>();
        edge->setWeight(m_weightEdit->text().toInt());
    }

    m_lastChangedObject = m_selectedObject;

    emit enableConfirmButton(false);
    emit objectChanged();

    updateContent();
    restoreSelection();
}

void ChangeObjectDialog::restoreSelection()
{
    if (m_lastChangedObject.canConvert<EmployeeNode*>()) {
        EmployeeNode* emplNode = m_lastChangedObject.value<EmployeeNode*>();
        restoreEmployeeNode(emplNode);
    } else if (m_lastChangedObject.canConvert<SkillNode*>()) {
        SkillNode* skillNode = m_lastChangedObject.value<SkillNode*>();
        restoreSkillNode(skillNode);
    } else if (m_lastChangedObject.canConvert<GraphEdge*>()) {
        GraphEdge* edge = m_lastChangedObject.value<GraphEdge*>();
        restoreEdge(edge);
    }
}

void ChangeObjectDialog::restoreEmployeeNode(EmployeeNode* node)
{
    for (int i = 0; i < m_objectsList->count(); i++) {
        QVariant object = m_objectsList->itemData(i);

        if (object.canConvert<EmployeeNode*>()) {
            EmployeeNode* selectedNode = object.value<EmployeeNode*>();
            if (selectedNode->getId() == node->getId()) {
                m_objectsList->setCurrentIndex(i);
                break;
            }
        }
    }
}

void ChangeObjectDialog::restoreSkillNode(SkillNode* node)
{
    for (int i = 0; i < m_objectsList->count(); i++) {
        QVariant object = m_objectsList->itemData(i);

        if (object.canConvert<SkillNode*>()) {
            SkillNode* selectedNode = object.value<SkillNode*>();
            if (selectedNode->getId() == node->getId()) {
                m_objectsList->setCurrentIndex(i);
                break;
            }
        }
    }
}

void ChangeObjectDialog::restoreEdge(GraphEdge* edge)
{
    for (int i = 0; i < m_objectsList->count(); i++) {
        QVariant object = m_objectsList->itemData(i);

        if (object.canConvert<GraphEdge*>()) {
            GraphEdge* selectedEdge = object.value<GraphEdge*>();
            if (selectedEdge->getSourceNode()->getId() == edge->getSourceNode()->getId() &&
                selectedEdge->getDestNode()->getId() == edge->getDestNode()->getId())
            {
                m_objectsList->setCurrentIndex(i);
                break;
            }
        }
    }
}

ChangeObjectDialog::~ChangeObjectDialog()
{
    m_graphicsView->scene()->clear();
}
