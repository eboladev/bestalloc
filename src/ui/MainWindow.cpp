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
#include <QFileDialog>
#include <QMessageBox>

#include "ConfigReader.h"

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_dataProvider(BestAllocAlgorithm()), m_graphWidget(this)
{
    initMenuBar();

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(&m_graphWidget);

    setCentralWidget(scrollArea);
    setWindowTitle(BESTALLOC_TITLE);

    QDesktopWidget desktopWidget;

    int windowWidth = 850;
    int windowHeight = 600;

    int screenWidth = desktopWidget.screen()->width();
    int screenHeight = desktopWidget.screen()->height();

    setGeometry(screenWidth / 2 - windowWidth / 2,
                screenHeight / 2 - windowHeight / 2,
                windowWidth, windowHeight);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    m_graphWidget.resizeToFit();
}

void MainWindow::initMenuBar()
{
    QMenu* menuFile  = createFileMenu();
    QMenu* menuEdit  = createEditMenu();
    QMenu* menuTools = createToolsMenu();

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuEdit);
    menuBar()->addMenu(menuTools);
}

QMenu* MainWindow::createFileMenu()
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

    return menuFile;
}

QMenu* MainWindow::createEditMenu()
{
    QAction* addDataAction = new QAction(NULL);
    addDataAction->setText(ADD_DATA_MENU_LABEL);
    connect(addDataAction, SIGNAL(triggered()), &m_graphWidget, SLOT(addNewNode()));

    QAction* changeObjectAction = new QAction(NULL);
    changeObjectAction->setText(EDIT_OBJECT_MENU_LABEL);
    connect(changeObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(changeObject()));

    QAction* deleteObjectAction = new QAction(NULL);
    deleteObjectAction->setText(DELETE_OBJECT_MENU_LABEL);
    connect(deleteObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(deleteObject()));

    QMenu* menuEdit = new QMenu(EDIT_MENU_LABEL);
    menuEdit->addAction(addDataAction);
    menuEdit->addAction(changeObjectAction);
    menuEdit->addAction(deleteObjectAction);
    return menuEdit;
}

QMenu* MainWindow::createToolsMenu()
{
    QAction* generateReportAction = new QAction(NULL);
    generateReportAction->setText(GENERATE_REPORT_ACTION_MENU_LABEL);
    connect(generateReportAction, SIGNAL(triggered()), SLOT(generateReport()));

    QAction* computeAction = new QAction(NULL);
    computeAction->setText(COMPUTE_LABEL);
    connect(computeAction, SIGNAL(triggered()), SLOT(compute()));

    QAction* resetGraphAction = new QAction(NULL);
    resetGraphAction->setText(RESET_GRAPH_LABEL);
    connect(resetGraphAction, SIGNAL(triggered()), &m_graphWidget, SLOT(reset()));

    QMenu* menuTools = new QMenu(TOOLS_MENU_LABEL);
    menuTools->addAction(computeAction);
    menuTools->addAction(resetGraphAction);
    menuTools->addAction(generateReportAction);

    return menuTools;
}

bool MainWindow::checkTaskInputData()
{
    foreach (EmployeeNode* node, m_graphWidget.getEmployeeNodes()) {
        if(node->getEdges().size()<=0){
            return false;
        }
    }

    foreach (SkillNode* node, m_graphWidget.getSkillNodes()) {
        if (node->getEdges().size()<=0){
            return false;
        }
    }

    bool result = m_graphWidget.getEmployeeNodes().size() == m_graphWidget.getSkillNodes().size();
    return result;
}

void MainWindow::compute()
{
    m_dataProvider.clearContainers();

    if(!checkTaskInputData()){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Can`t compute");
        msgBox.setInformativeText(
                    "1) The number of peaks in different parts should be the same; \n"
                    "2) There must not be connected vertices, each vertex must be connected with anything;"
                    );
        msgBox.exec();
        return;
    }

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
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save task to file"), "/home", tr("Best files (*.bst)"));
    if(fileName!=""){
        ConfigReader::save(fileName+".bst",m_dataProvider,m_graphWidget);
    }
}

void MainWindow::loadState()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load task from file"), "/home", tr("Best files (*.bst)"));
    if(fileName!=""){
        ConfigReader::load(fileName,m_dataProvider,m_graphWidget);
    }
}

void MainWindow::generateReport()
{
    const QString xml_ext = "xml";
    const QString csv_ext = "csv";
    const QString text_ext = "txt";
    const QString point = ".";
    DataConverter *dataConverter;
    QString selectedFilter = "";
    QFileDialog filedialog;
    QString f_name = filedialog.getSaveFileName(this,
                                                tr("Generate report"),
                                                QDir::currentPath(),
                                                tr(TEXT_FILE_FILTER";;"CSV_FILE_FILTER";;"XML_FILE_FILTER),
                                                &selectedFilter);
    if (f_name != ""){
        QFileInfo fileInfo(f_name);
        if (fileInfo.suffix().isEmpty() || !((fileInfo.suffix() == text_ext && selectedFilter == TEXT_FILE_FILTER)||
                                             (fileInfo.suffix() == csv_ext && selectedFilter == CSV_FILE_FILTER)  ||
                                             (fileInfo.suffix() == xml_ext && selectedFilter == XML_FILE_FILTER)))
        if(selectedFilter == TEXT_FILE_FILTER)
            f_name += point + text_ext;
        else if(selectedFilter == CSV_FILE_FILTER)
            f_name += point + csv_ext;
        else if(selectedFilter == XML_FILE_FILTER)
            f_name += point + xml_ext;
        qDebug() <<f_name;

        QFileInfo fileInfoChecked(f_name);

        if(fileInfoChecked.suffix() == text_ext)
            dataConverter = new TextDataConverter();
        else if(fileInfoChecked.suffix() == csv_ext)
            dataConverter = new CSVDataConverter();
        else if(fileInfoChecked.suffix() == xml_ext)
            dataConverter = new XMLDataConverter();

        ReportGenerator reportGenerator(f_name, dataConverter);
        reportGenerator.setEmployeeNodes(m_graphWidget.getEmployeeNodes());
        reportGenerator.setSkillNodes(m_graphWidget.getSkillNodes());
        reportGenerator.setEdges(m_graphWidget.getEdges());
        reportGenerator.setBestAllocMap(m_dataProvider.getBestAllocation());
        reportGenerator.generateReport();

        delete dataConverter;
    }
}

MainWindow::~MainWindow()
{
}
