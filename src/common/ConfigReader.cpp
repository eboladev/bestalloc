/*! ---------------------------------------------------------------
 * \file   ConfigReader.cpp
 * \brief  ConfigReader class implementation
 * \author Dmitry Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "ConfigReader.h"

using namespace bestalloc;


ConfigReader::ConfigReader()
{
}


void ConfigReader::save(QString filename,
                                   bestalloc::DataProvider &dataProvider,
                                   bestalloc::GraphWidget &graphWidget)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QDataStream str(&file);
    graphWidget.save(str);
    file.close();
}

void ConfigReader::load(QString filename,
                                      bestalloc::DataProvider &dataProvider,
                                      bestalloc::GraphWidget &graphWidget)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QDataStream str(&file);
    graphWidget.load(str);
    file.close();
}

string ConfigReader::readString(QDataStream &str)
{
    string result;
    char * tmp = new char[MAX_STRING_SIZE];
    str>>tmp;
    if(tmp){
        result = tmp;
    }else{
        qDebug()<<"readString error\n";
        throw;
    }
    return result;
}

void ConfigReader::saveQPointF(QDataStream &str, QPointF &arg)
{
    str<<arg;
}

void ConfigReader::loadQPointF(QDataStream &str, QPointF &arg)
{
    str>>arg;
}

void ConfigReader::saveQPixmap(QDataStream &str, QPixmap &arg)
{
    str<<arg;
}

void ConfigReader::loadQPixmap(QDataStream &str, QPixmap &arg)
{
    str>>arg;
}
