/*! ---------------------------------------------------------------
 * \file   EditNodeDialog.cpp
 * \brief  EditNodeDialog class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "EditNodeDialog.h"
#include "EmployeeNode.h"
#include "SkillNode.h"
#include "GraphWidget.h"
#include "Constants.h"
using namespace bestalloc;

#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QFileDialog>
#include <QMessageBox>

EditNodeDialog::EditNodeDialog(NodeTypes nodeType, int nodeId, GraphWidget* parent)
    : QDialog(parent),
      m_widget(parent),
      m_nodeType(nodeType),
      m_nodeId(nodeId),
      m_nodeName(""),
      m_nodeImage(NULL)
{
    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setMaxLength(MAX_NODE_NAME_LENGTH);
    connect(m_nameEdit, SIGNAL(textChanged(QString)), this, SLOT(changeNodeName(QString)));
    connect(this, SIGNAL(enableEdition(bool)), m_nameEdit, SLOT(setEnabled(bool)));

    QLabel* nameLabel = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    nameLabel->setBuddy(m_nameEdit);
    connect(this, SIGNAL(enableEdition(bool)), nameLabel, SLOT(setEnabled(bool)));

    QLabel* labelImg = new QLabel(GRAPH_NODE_IMAGE_LABEL, this);
    connect(this, SIGNAL(enableEdition(bool)), labelImg, SLOT(setEnabled(bool)));

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, IMAGE_PREVIEW_SIZE, IMAGE_PREVIEW_SIZE);

    m_graphicsView = new QGraphicsView(this);
    m_graphicsView->setScene(scene);
    m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    connect(this, SIGNAL(enableEdition(bool)), m_graphicsView, SLOT(setEnabled(bool)));

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(m_nameEdit);

    QPushButton* openPictureBtn = new QPushButton(SELECT_PICTURE_LABEL, this);
    connect(openPictureBtn, SIGNAL(clicked()), SLOT(openPicture()));
    connect(this, SIGNAL(enableEdition(bool)), openPictureBtn, SLOT(setEnabled(bool)));

    QHBoxLayout* layoutImg = new QHBoxLayout;
    layoutImg->addWidget(labelImg);
    layoutImg->addWidget(openPictureBtn);

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
    rightLayout->addLayout(nameLayout);
    rightLayout->addWidget(m_graphicsView);
    rightLayout->addLayout(layoutImg);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(EDIT_NODE_LABEL);

    updateContent();
}

void EditNodeDialog::updateContent()
{
    m_graphicsView->scene()->clear();

    if (m_nodeType == EMPLOYEE_TYPE) {
        EmployeeNode* emplNode = m_widget->getEmployeeNodeById(m_nodeId);
        if (emplNode != NULL) {
            m_nodeName = QString::fromStdString(emplNode->getName());
            m_nameEdit->setText(m_nodeName);

            m_nodeImage = new QGraphicsPixmapItem(emplNode->getNodePicture()
                                                  .scaledToHeight(IMAGE_PREVIEW_SIZE)
                                                  .scaledToWidth(IMAGE_PREVIEW_SIZE));
            m_graphicsView->scene()->addItem(m_nodeImage);
        } else {
            m_nodeId = -1;
            m_nodeName = "";
            m_nameEdit->setText("");
            m_nodeImage = NULL;

            emit enableEdition(false);
        }
    } else {
        SkillNode* skillNode = m_widget->getSkillNodeById(m_nodeId);
        if (skillNode != NULL) {
            m_nodeName = QString::fromStdString(skillNode->getName());
            m_nameEdit->setText(m_nodeName);

            m_nodeImage = new QGraphicsPixmapItem(skillNode->getNodePicture()
                                                  .scaledToHeight(IMAGE_PREVIEW_SIZE)
                                                  .scaledToWidth(IMAGE_PREVIEW_SIZE));
            m_graphicsView->scene()->addItem(m_nodeImage);
        } else {
            m_nodeId = -1;
            m_nodeName = "";
            m_nameEdit->setText("");
            m_nodeImage = NULL;

            emit enableEdition(false);
        }
    }
}

void EditNodeDialog::changeNodeName(const QString& value)
{
    emit(enableConfirmButton(m_nodeName != value && value != ""));
}

void EditNodeDialog::openPicture()
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

void EditNodeDialog::confirmChanges()
{
    if (m_widget == NULL) return;

    if (m_nodeType == EMPLOYEE_TYPE) {
        EmployeeNode* emplNode = m_widget->getEmployeeNodeById(m_nodeId);
        if (emplNode != NULL) {
            string newNodeName = m_nameEdit->text().toStdString();

            QList<EmployeeNode*> employees = m_widget->getEmployeeNodes();
            foreach (EmployeeNode* node, employees) {
                if (node->getName() == newNodeName && node->getId() != emplNode->getId()) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(WARNING_TITLE);
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setText(EDIT_EMPLOYEE_ERROR_TEXT);
                    msgBox.setInformativeText(EDIT_EMPLOYEE_ERROR_INFO);
                    msgBox.exec();

                    return;
                }
            }

            emplNode->setName(newNodeName);
            emplNode->setNodePicture(m_nodeImage->pixmap());

            emit enableConfirmButton(false);
            emit objectChanged();

            return;

        }
    } else {
        SkillNode* skillNode = m_widget->getSkillNodeById(m_nodeId);
        if (skillNode != NULL) {
            string newNodeName = m_nameEdit->text().toStdString();

            QList<SkillNode*> skills = m_widget->getSkillNodes();
            foreach (SkillNode* node, skills) {
                if (node->getName() == newNodeName && node->getId() != skillNode->getId()) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(WARNING_TITLE);
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setText(EDIT_SKILL_ERROR_TEXT);
                    msgBox.setInformativeText(EDIT_SKILL_ERROR_INFO);
                    msgBox.exec();

                    return;
                }
            }

            skillNode->setName(newNodeName);
            skillNode->setNodePicture(m_nodeImage->pixmap());

            emit enableConfirmButton(false);
            emit objectChanged();

            return;
        }
    }
}

EditNodeDialog::~EditNodeDialog()
{
}
