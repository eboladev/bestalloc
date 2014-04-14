/*! ---------------------------------------------------------------
 * \file   main.cpp
 * \brief  Source file for executing test suites
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc/tst
 * ---------------------------------------------------------------- */

#include <QtTest/QtTest>
#include <QtCore/QtCore>

#include "Test_Skill.h"
#include "Test_Employee.h"
#include "Test_BestAllocAlgo.h"
#include "Test_Edge.h"

int main(int argc, char **argv)
{
    QObject* tests[] = {
        new test::Test_Skill(),
        new test::Test_Employee(),
        new test::Test_BestAllocAlgo(),
        new test::Test_Edge()

    };

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(QObject*); i++) {
        QTest::qExec(tests[i]);
    }

    return 0;
}
