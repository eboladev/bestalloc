/*! ---------------------------------------------------------------
 * \file   ConfigReader.h
 * \brief  ConfigReader class declaration
 * \author Dmitry Vasiliev
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QDataStream>
#include <QString>
#include "GraphWidget.h"

namespace bestalloc
{
    class ConfigReader
    {
    public:
        static void save(QString filename, GraphWidget* graphWidget);
        static void load(QString filename, GraphWidget* graphWidget);
    };
}
#endif // CONFIGREADER_H
