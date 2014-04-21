/*! ---------------------------------------------------------------
 * \file   Test_BestAllocAlgo.h
 * \brief  Test suite for BestAllocAlgo class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#ifndef TEST_BESTALLOCALGO_H
#define TEST_BESTALLOCALGO_H

#include <QObject>
#include <QTest>
#include <Employee.h>
#include <Skill.h>

namespace test
{
    class Test_BestAllocAlgo : public QObject
    {
        Q_OBJECT
    public:
        Test_BestAllocAlgo();

    private slots:
        void getEmployeeById();
        void getSkillById();
        void isSkillExists();
        void  getSkillLevel();
        void initEffMatrix();
        void addEmployee();
        void addSkill();
        void assignSkill();
        void getBestAllocation();
        void clearContainers();

    };
}
#endif // TEST_BESTALLOCALGO_H
