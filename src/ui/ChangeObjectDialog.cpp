/*! ---------------------------------------------------------------
 * \file   ChangeObjectDialog.cpp
 * \brief  ChangeObjectDialog class implementation
 * \author Dmitriy Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "ChangeObjectDialog.h"
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
#include <QGraphicsView>
#include <QFileDialog>
#include <QIntValidator>

#define IMAGE_PREVIEW_SIZE 300

ChangeObjectDialog::ChangeObjectDialog(QWidget *parent)
    : QDialog(parent), m_currentImage(NULL)//, m_selectedObject(NULL),
{
    m_objectsList = new QComboBox(this);
    connect(m_objectsList, SIGNAL(currentIndexChanged(int)), SLOT(selectObject(int)));

    m_editName = new QLineEdit(this);

    QLabel* labelName = new QLabel(GRAPH_NODE_NAME_LABEL, this);
    labelName->setBuddy(m_editName);

    QLabel* labelImg = new QLabel(GRAPH_NODE_IMAGE_LABEL, this);

    QGraphicsView *view = new QGraphicsView(this);
    m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(0, 0, IMAGE_PREVIEW_SIZE, IMAGE_PREVIEW_SIZE);
    view->setScene(m_scene);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setRenderHint(QPainter::Antialiasing);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    m_editPower = new QLineEdit(this);
    QIntValidator *validator = new QIntValidator(this);
    validator->setBottom(0);
    m_editPower->setValidator(validator);

    QLabel* labelPower = new QLabel(GRAPH_NODE_WEIGHT_LABEL, this);
    labelPower->setBuddy(m_editPower);

    QHBoxLayout *layoutName = new QHBoxLayout;
    layoutName->addWidget(labelName);
    layoutName->addWidget(m_editName);

    m_openPictureBtn = new QPushButton(SELECT_PICTURE_LABEL, this);
    connect(m_openPictureBtn, SIGNAL(clicked()), SLOT(openPicture()));

    QHBoxLayout *layoutImg = new QHBoxLayout;
    layoutImg->addWidget(labelImg);
    layoutImg->addWidget(m_openPictureBtn);

    QHBoxLayout *layoutPower = new QHBoxLayout;
    layoutPower->addWidget(labelPower);
    layoutPower->addWidget(m_editPower);

    QPushButton * confirmButton = new QPushButton(CONFIRM_LABEL, this);
    confirmButton->setDefault(true);
    connect(confirmButton, SIGNAL(clicked()), SLOT(confirmChanges()));

    QPushButton* closeButton = new QPushButton(CANCEL_LABEL, this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *layoutBtns = new QHBoxLayout;
    layoutBtns->addWidget(confirmButton);
    layoutBtns->addWidget(closeButton);

    QVBoxLayout *rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(m_objectsList);
    rightLayout->addLayout(layoutName);
    rightLayout->addWidget(view);
    rightLayout->addLayout(layoutImg);
    rightLayout->addLayout(layoutPower);
    rightLayout->addLayout(layoutBtns);

    setWindowTitle(CHANGE_OBJECT_LABEL);
}

ChangeObjectDialog::~ChangeObjectDialog()
{
}

/*void ChangeObjectDialog::addElement(TaskObject *obj)
{
    QVariant v = QVariant::fromValue(obj);
    m_objectsList->addItem(obj->getTaskName(),v);
}*/

void ChangeObjectDialog::selectObject(int index)
{
/*    m_scene->clear();
    QVariant v = m_objectsList->itemData(index);
    TaskObject *obj = v.value<TaskObject*>();
    m_selectedObject = obj;
    obj->printTo(m_editName,m_editPower);
    m_currentImage = (QGraphicsPixmapItem*)obj->getGraphItem();
    if(m_currentImage){
        QPixmap pixmap = m_currentImage->pixmap();
        m_currentImage->setPixmap(pixmap.scaledToHeight(IMAGE_PREVIEW_SIZE).scaledToWidth(IMAGE_PREVIEW_SIZE));
        m_scene->addItem(m_currentImage);
    }
    m_openPictureBtn->setEnabled(m_currentImage);*/
}

void ChangeObjectDialog::confirmChanges()
{
/*    if(!m_selectedObject){
        return;
    }
    m_selectedObject->setFrom(m_editName,m_editPower);
    if(m_currentImage){
        m_selectedObject->setImage(m_currentImage);
    }
    m_objectsList->setEnabled(false);
    emit(updateImage());*/
}

void ChangeObjectDialog::openPicture()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select picture file"), ":/images", tr("png (*.png)"));
    if(fileName!=""){
        m_currentImage = new QGraphicsPixmapItem(QPixmap(fileName));
        m_scene->clear();
        if(m_currentImage){
            m_scene->addItem(m_currentImage);
        }
    }
}
