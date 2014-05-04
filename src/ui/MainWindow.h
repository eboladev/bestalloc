/*! ---------------------------------------------------------------
 * \file   MainWindow.h
 * \brief  MainWindow class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QMainWindow>
#include <QSharedPointer>
#include <QFileDialog>

#include "DataProvider.h"
#include "GraphWidget.h"

#include "ReportGenerator.h"
#include "XMLDataConverter.h"
#include "CSVDataConverter.h"
#include "TextDataConverter.h"


namespace bestalloc
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        DataProvider m_dataProvider;
        GraphWidget  m_graphWidget;

    protected:
        void resizeEvent(QResizeEvent* event);

    private:
        void initMenuBar();
        QMenu* createFileMenu();
        QMenu* createEditMenu();
        QMenu* createToolsMenu();

        bool validateInputData();

    public:
        MainWindow(QWidget* parent = NULL);
        ~MainWindow();

    public slots:
        void compute();

        void saveState();
        void loadState();

        void generateReport();
    };
}

#endif // MAINWINDOW_H_INCLUDED
