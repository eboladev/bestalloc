/*! ---------------------------------------------------------------
 * \file   main.cpp
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include <QApplication>

#include "MainWindow.h"
using namespace bestalloc;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
