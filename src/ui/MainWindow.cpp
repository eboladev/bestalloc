/*! ---------------------------------------------------------------
 * \file   MainWindow.cpp
 * \brief  MainWindow class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "MainWindow.h"
#include "Constants.h"
#include "ConfigReader.h"
using namespace bestalloc;

#include <QMenuBar>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QStatusBar>
#include <QProcess>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), m_dataProvider(BestAllocAlgorithm()), m_graphWidget(this), m_helpProcess(new QProcess())
{
    initMenuBar();

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(&m_graphWidget);

    setCentralWidget(scrollArea);
    setWindowTitle(BESTALLOC_TITLE);

    statusBar()->addWidget(new QLabel(STATUS_LABEL, this));

    QLabel* statusLabel = new QLabel("", this);
    statusBar()->addWidget(statusLabel);
    connect(this, SIGNAL(setStatus(QString)), statusLabel, SLOT(setText(QString)));

    QDesktopWidget desktopWidget;

    int windowWidth = 850;
    int windowHeight = 600;

    int screenWidth = desktopWidget.screen()->width();
    int screenHeight = desktopWidget.screen()->height();

    setGeometry(screenWidth / 2 - windowWidth / 2,
                screenHeight / 2 - windowHeight / 2,
                windowWidth, windowHeight);

    connect(&m_graphWidget, SIGNAL(compute()), SLOT(compute()));
    connect(&m_graphWidget, SIGNAL(report()), SLOT(generateReport()));
    connect(&m_graphWidget, SIGNAL(contentChanged()), SLOT(updateStatus()));

    updateStatus();
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
    QMenu* menuHelp  = createHelpMenu();

    menuBar()->addMenu(menuFile);
    menuBar()->addMenu(menuEdit);
    menuBar()->addMenu(menuTools);
    menuBar()->addMenu(menuHelp);
}

QMenu* MainWindow::createFileMenu()
{
    QAction* saveAction = new QAction(this);
    saveAction->setText(SAVE_ACTION_MENU_LABEL);
    connect(saveAction, SIGNAL(triggered()), SLOT(saveState()));

    QAction* loadAction = new QAction(this);
    loadAction->setText(LOAD_ACTION_MENU_LABEL);
    connect(loadAction, SIGNAL(triggered()), SLOT(loadState()));

    QMenu* menuFile = new QMenu(FILE_MENU_LABEL, this);
    menuFile->addAction(saveAction);
    menuFile->addAction(loadAction);

    return menuFile;
}

QMenu* MainWindow::createEditMenu()
{
    QAction* addObjectAction = new QAction(this);
    addObjectAction->setText(ADD_OBJECT_MENU_LABEL);
    connect(addObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(addObject()));
    connect(addObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(resetLastCtxtMenuPosition()));

    QAction* changeObjectAction = new QAction(this);
    changeObjectAction->setText(CHANGE_OBJECT_MENU_LABEL);
    connect(changeObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(changeObject()));

    QAction* deleteObjectAction = new QAction(this);
    deleteObjectAction->setText(DELETE_OBJECT_MENU_LABEL);
    connect(deleteObjectAction, SIGNAL(triggered()), &m_graphWidget, SLOT(deleteObject()));

    QMenu* menuEdit = new QMenu(EDIT_MENU_LABEL, this);
    menuEdit->addAction(addObjectAction);
    menuEdit->addAction(changeObjectAction);
    menuEdit->addAction(deleteObjectAction);

    return menuEdit;
}

QMenu* MainWindow::createToolsMenu()
{
    QAction* computeAction = new QAction(this);
    computeAction->setText(COMPUTE_LABEL);
    connect(computeAction, SIGNAL(triggered()), SLOT(compute()));

    QAction* resetGraphAction = new QAction(this);
    resetGraphAction->setText(RESET_GRAPH_LABEL);
    connect(resetGraphAction, SIGNAL(triggered()), &m_graphWidget, SLOT(reset()));

    QAction* generateReportAction = new QAction(this);
    generateReportAction->setText(GENERATE_REPORT_ACTION_MENU_LABEL);
    connect(generateReportAction, SIGNAL(triggered()), SLOT(generateReport()));

    QMenu* menuTools = new QMenu(TOOLS_MENU_LABEL, this);
    menuTools->addAction(computeAction);
    menuTools->addAction(resetGraphAction);
    menuTools->addAction(generateReportAction);

    return menuTools;
}

QMenu* MainWindow::createHelpMenu()
{
    QAction* helpAction = new QAction(this);
    helpAction->setText(HELP_MENU_LABEL);
    connect(helpAction, SIGNAL(triggered()), SLOT(showHelp()));

    QMenu* menuHelp = new QMenu(HELP_MENU_LABEL, this);
    menuHelp->addAction(helpAction);

    return menuHelp;
}

bool MainWindow::validateInputData()
{
    foreach (EmployeeNode* node, m_graphWidget.getEmployeeNodes()) {
        if (node->getEdges().size() <= 0){
            return false;
        }
    }

    foreach (SkillNode* node, m_graphWidget.getSkillNodes()) {
        if (node->getEdges().size() <= 0){
            return false;
        }
    }

    bool result = m_graphWidget.getEmployeeNodes().size() == m_graphWidget.getSkillNodes().size();
    return result;
}

void MainWindow::compute()
{
    m_dataProvider.clearContainers();

    if (!validateInputData()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(WARNING_TITLE);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(CALC_WARNING_TEXT);
        msgBox.setInformativeText(CALC_WARNING_INFO);
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
        tr(SAVE_CONFIGURATION_LABEL), QDir::currentPath(), tr(CONFIGURATION_FILE_FILTER));
    if (fileName != "") {
        ConfigReader::save(fileName, &m_graphWidget);
    }
}

void MainWindow::loadState()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr(LOAD_CONFIGURATION_LABEL), QDir::currentPath(), tr(CONFIGURATION_FILE_FILTER));
    if (fileName != "") {
        ConfigReader::load(fileName, &m_graphWidget);
    }
}

void MainWindow::updateStatus()
{
    QList<EmployeeNode*> employees = m_graphWidget.getEmployeeNodes();
    QList<SkillNode*> skills = m_graphWidget.getSkillNodes();

    QString status = QString(EMPLOYEES_LABEL) + ": " + QString::number(employees.count()) + ";  " +
                     QString(SKILLS_LABEL) + ": " + QString::number(skills.count());
    setStatus(status);
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
    QString f_name = filedialog.getSaveFileName(this, tr(GENERATE_REPORT_LABEL), QDir::currentPath(),
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

void MainWindow::showHelp()
{
    QProcess::ProcessState state = m_helpProcess->state();
    if (state == QProcess::NotRunning) {
        QLatin1String filename1(DEFAULT_HELP_FILE_PATH);
        QLatin1String filename2(INSTALLED_HELP_FILE_PATH);

        QFile helpFile1(filename1);
        QFile helpFile2(filename2);

        if (!helpFile1.exists() && !helpFile2.exists()) {
            QMessageBox msgBox;
            msgBox.setWindowTitle(WARNING_TITLE);
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText(HELP_RUNNING_WARNING_TEXT);
            msgBox.setInformativeText(HELP_NOT_FOUND_ERROR_INFO);
            msgBox.exec();

            return;
        }

        QStringList args("-collectionFile");

        if (helpFile1.exists()) {
            args << filename1;
        } else if (helpFile2.exists()) {
            args << filename2;
        }

        m_helpProcess->start(QLatin1String("assistant"), args);

    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle(WARNING_TITLE);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText(HELP_RUNNING_WARNING_TEXT);
        msgBox.setInformativeText(HELP_RUNNING_WARNING_INFO);
        msgBox.exec();
    }
}

MainWindow::~MainWindow()
{
    m_helpProcess->kill();
    delete(m_helpProcess);
}
