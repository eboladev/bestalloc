/*! ---------------------------------------------------------------
 * \file   MainWindow.cpp
 * \brief  MainWindow class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "MainWindow.h"
#include "Constants.h"
using namespace bestalloc;

#include <QMenuBar>
#include <QDesktopWidget>

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_dataProvider(BestAllocAlgorithm()), m_graphWidget()
{
    initMenuBar();

    setCentralWidget(&m_graphWidget);
    setWindowTitle(BESTALLOC_TITLE);

    QDesktopWidget desktopWidget;

    int windowWidth = 1024;
    int windowHeight = 768;

    int screenWidth = desktopWidget.screen()->width();
    int screenHeight = desktopWidget.screen()->height();

    setGeometry(screenWidth / 2 - windowWidth / 2,
                screenHeight / 2 - windowHeight / 2,
                windowWidth, windowHeight);

    connect(&m_graphWidget, SIGNAL(compute()), SLOT(compute()));
}

void MainWindow::initMenuBar()
{
    QAction* saveAction = new QAction(NULL);
    saveAction->setText(SAVE_ACTION_MENU_LABEL);
    connect(saveAction, SIGNAL(triggered()), SLOT(saveState()));

    QAction* loadAction = new QAction(NULL);
    loadAction->setText(LOAD_ACTION_MENU_LABEL);
    connect(loadAction, SIGNAL(triggered()), SLOT(loadState()));

    QMenu* menuFile = new QMenu(FILE_MENU_LABEL);
    menuFile->addAction(saveAction);
    menuFile->addAction(loadAction);

    QAction* addDataAction = new QAction(NULL);
    addDataAction->setText(ADD_DATA_MENU_LABEL);
    connect(addDataAction, SIGNAL(triggered()), &m_graphWidget, SLOT(addNewNode()));

    QAction* addTemplateAction = new QAction(NULL);
    addTemplateAction->setText(ADD_TEMPLATE_MENU_LABEL);
    connect(addDataAction, SIGNAL(triggered()), SLOT(addTemplate()));

    QAction* changeObjectAction = new QAction(NULL);
    changeObjectAction->setText(CHANGE_OBJECT_MENU_LABEL);
    connect(changeObjectAction, SIGNAL(triggered()), SLOT(changeObject()));

    QAction* deleteObjectAction = new QAction(NULL);
    deleteObjectAction->setText(DELETE_OBJECT_MENU_LABEL);
    connect(deleteObjectAction, SIGNAL(triggered()), SLOT(deleteObject()));

    QMenu* menuEdit = new QMenu(EDIT_MENU_LABEL);
    menuEdit->addAction(addDataAction);
    menuEdit->addAction(addTemplateAction);
    menuEdit->addAction(changeObjectAction);
    menuEdit->addAction(deleteObjectAction);

    QAction* generateReportAction = new QAction(NULL);
    generateReportAction->setText(GENERATE_REPORT_ACTION_MENU_LABEL);
    connect(generateReportAction, SIGNAL(triggered()), SLOT(generateReport()));

    QMenu* menuTools = new QMenu(TOOLS_MENU_LABEL);
    menuTools->addAction(generateReportAction);

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuEdit);
    menuBar()->addMenu(menuTools);
}

void MainWindow::compute()
{
    foreach (EmployeeNode* node, m_graphWidget.getEmployeeNodes()) {
        m_dataProvider.addEmployee(*node);
    }

    foreach (SkillNode* node, m_graphWidget.getSkillNodes()) {
        m_dataProvider.addSkill(*node);
    }

    foreach (GraphEdge* edge, m_graphWidget.getEdges()) {
        m_dataProvider.assignSkill(edge->getSourceNode()->getId(), edge->getDestNode()->getId(), edge->getWeight());
    }

    vector< pair<Employee, Skill> > bestAllocMap = m_dataProvider.getBestAllocation();
    m_graphWidget.setBestAllocation(bestAllocMap);
}

void MainWindow::saveState()
{
    // TODO
}

void MainWindow::loadState()
{
    // TODO
}

void MainWindow::addTemplate()
{
    // TODO
}

void MainWindow::changeObject()
{
    // TODO
}

void MainWindow::deleteObject()
{
    // TODO
}

void MainWindow::generateReport()
{
    // TODO
}

MainWindow::~MainWindow()
{
}
