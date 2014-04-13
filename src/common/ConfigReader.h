/*! ---------------------------------------------------------------
 * \file   ConfigReader.h
 * \brief  ConfigReader class declaration
 * \author Dmitry Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "Constants.h"
#include "DataProvider.h"
#include "GraphWidget.h"

namespace bestalloc {

    class DataProvider;
    class ConfigReader
    {
    public:
        ConfigReader();
        static void save(QString filename,
                         DataProvider &dataProvider,
                         GraphWidget &graphWidget);
        static void load(QString filename,
                            DataProvider &dataProvider,
                            GraphWidget  &graphWidget);
        static string readString(QDataStream &str);
        static void saveQPointF(QDataStream &str,QPointF &arg);
        static void loadQPointF(QDataStream &str,QPointF &arg);
        static void saveQPixmap(QDataStream &str,QPixmap &arg);
        static void loadQPixmap(QDataStream &str,QPixmap &arg);
    };
}
#endif // CONFIGREADER_H
