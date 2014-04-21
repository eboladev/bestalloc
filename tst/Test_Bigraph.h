/*! ---------------------------------------------------------------
 * \file   Test_Bigraph.h
 * \brief  Test suite for Bigraph class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#ifndef TEST_BIGRAPH_H
#define TEST_BIGRAPH_H

#include <QObject>
#include <QTest>
#include <QDebug>

#include "Bigraph.h"
#include "BigraphIterator.h"
//#include "Employee.h"
//#include "Skill.h"
//typedef int U;
//typedef float V;

namespace test{

    class Test_Bigraph : public QObject
    {
        Q_OBJECT
    public:
        Test_Bigraph();

    private slots:
        void  getUSetSize();
        void  getVSetSize();
        void  getEdgesCount();

        void addEdge();
        void addUVertex();
        void addVVertex();

        void clear();

        //typedef BigraphIterator<U> UIterator;

        void uSetStart();
        void uSetItemAt();
        void uSetEnd();

        //typedef BigraphIterator<V> VIterator;
        void vSetStart();
        void vSetItemAt();
        void vSetEnd();

        //typedef BigraphIterator< Edge<U, V> > EdgeIterator;
        void edgesStart();
        void edgesItemAt();
        void edgesEnd();

    };
}

#endif // TEST_BIGRAPH_H
