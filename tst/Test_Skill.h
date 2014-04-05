/*! ---------------------------------------------------------------
 * \file   Test_Skill.h
 * \brief  Test suite for Skill class
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc/tst
 * ---------------------------------------------------------------- */

#ifndef TEST_SKILL_H
#define TEST_SKILL_H

#include <QObject>
#include <QtTest>

namespace test
{
    class Test_Skill : public QObject
    {
        Q_OBJECT

    public:
        Test_Skill();

    private slots:
        void getId();
        void setId();
        void getName();
        void setName();
    };

}

#endif // TEST_SKILL_H
