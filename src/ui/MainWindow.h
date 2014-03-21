/*! ---------------------------------------------------------------
 * \file   MainWindow.h
 * \brief  MainWindow class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>
#include <QSharedPointer>

#include "DataProvider.h"
#include "GraphWidget.h"

namespace bestalloc
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    private:
        DataProvider m_dataProvider;
        GraphWidget  m_graphWidget;

    private:
        void initMenuBar();

    public:
        MainWindow(QWidget* parent = NULL);

        ~MainWindow();

    public slots:
        void compute();

        void saveState();
        void loadState();

        void addTemplate();
        void changeObject();
        void deleteObject();

        void generateReport();
    };
}

#endif // MAIN_WINDOW_H_INCLUDED
