/*! ---------------------------------------------------------------
 * \file   Test_Skill.cpp
 * \brief  Test suite for Skill class
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc/tst
 * ---------------------------------------------------------------- */

#include "Test_Skill.h"
#include "Skill.h"
using namespace bestalloc;
using namespace test;

Test_Skill::Test_Skill()
{
}

void Test_Skill::getId()
{
    int id = 5;
    string name = "SkillName";

    Skill testSkill(id, name);

    QVERIFY(testSkill.getId() == id);
}

void Test_Skill::setId()
{
    Skill testSkill;

    int id = 5;
    testSkill.setId(id);

    QVERIFY(testSkill.getId() == id);
}

void Test_Skill::getName()
{
    int id = 5;
    string name = "SkillName";

    Skill testSkill(id, name);

    QVERIFY(testSkill.getName() == name);
}

void Test_Skill::setName()
{
    Skill testSkill;

    string name = "SkillName";
    testSkill.setName(name);

    QVERIFY(testSkill.getName() == name);
}
