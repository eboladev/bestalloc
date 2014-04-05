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

int main(int argc, char **argv)
{
    QObject* tests[] = {
        new test::Test_Skill()
    };

    for (unsigned int i = 0; i < sizeof(tests) / sizeof(QObject*); i++) {
        QTest::qExec(tests[i]);
    }

    return 0;
}
