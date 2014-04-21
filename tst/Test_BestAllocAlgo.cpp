/*! ---------------------------------------------------------------
 * \file   Test_BestAllocAlgo.cpp
 * \brief  Test suite for BestAllocAlgo class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "Test_BestAllocAlgo.h"
#include "BestAllocAlgo.h"
using namespace bestalloc;
using namespace test;

Test_BestAllocAlgo::Test_BestAllocAlgo()
{
}

void Test_BestAllocAlgo::getEmployeeById()
{
    int id = 2;
    string name = "EmployeeName";

    Employee employee(id, name);
    BestAllocAlgorithm test_algo;
    test_algo.addEmployee(employee);

    const Employee *employee_ref = test_algo.getEmployeeById(id);
    QVERIFY(employee_ref->getId() == id);
}

void Test_BestAllocAlgo::getSkillById()
{
    int id = 2;
    string name = "SKillName";

    Skill skill(id, name);
    BestAllocAlgorithm test_algo;
    test_algo.addSkill(skill);

    const Skill *skill_ref = test_algo.getSkillById(id);
    QVERIFY(skill_ref->getId() == id);
}

void Test_BestAllocAlgo::isSkillExists()
{
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    BestAllocAlgorithm test_algo;

    test_algo.addSkill(skill);
    test_algo.addEmployee(employee);

    test_algo.m_graph.addEdge(Edge<Employee, Skill>(employee, skill, 1));

    QVERIFY(test_algo.isSkillExists(id_e, id_s));
}

void  Test_BestAllocAlgo::getSkillLevel()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    BestAllocAlgorithm test_algo;

    test_algo.addSkill(skill);
    test_algo.addEmployee(employee);

    test_algo.m_graph.addEdge(Edge<Employee, Skill>(employee, skill, test_level));

    QVERIFY(test_algo.getSkillLevel(id_e, id_s) == test_level);
}

void Test_BestAllocAlgo::initEffMatrix()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    BestAllocAlgorithm test_algo;

    test_algo.addSkill(skill);
    test_algo.addEmployee(employee);

    test_algo.assignSkill(id_e, id_s, test_level);
    test_algo.initEffMatrix();
    QVERIFY(test_algo.m_effMatrix[0][0] == test_level);

}

void Test_BestAllocAlgo::addEmployee()
{
    int id = 2;
    string name = "EmployeeName";

    Employee employee(id, name);
    BestAllocAlgorithm test_algo;
    test_algo.addEmployee(employee);

    const Employee *employee_ref = test_algo.getEmployeeById(id);
    QVERIFY(employee_ref != NULL);
    QVERIFY(employee_ref->getName() == name);
}

void Test_BestAllocAlgo::addSkill()
{
    int id = 2;
    string name = "SKillName";

    Skill skill(id, name);
    BestAllocAlgorithm test_algo;
    test_algo.addSkill(skill);

    const Skill *skill_ref = test_algo.getSkillById(id);
    QVERIFY(skill_ref != NULL);
    QVERIFY(skill_ref->getName() == name);
}

void Test_BestAllocAlgo::assignSkill()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    BestAllocAlgorithm test_algo;

    test_algo.addSkill(skill);
    test_algo.addEmployee(employee);

    test_algo.assignSkill(id_e, id_s, test_level);

    QVERIFY(test_algo.isSkillExists(id_e, id_s));
    QVERIFY(test_algo.getSkillLevel(id_e, id_s) == test_level);
}

void Test_BestAllocAlgo::getBestAllocation()
{
    int allocation_size = 5;
    BestAllocAlgorithm test_algo;
    for(int i = 0; i< allocation_size; i++){
        int test_level = 1 + i;
        int id_s = 2 + i;
        string name_s = "SKillName";
        Skill skill(id_s, name_s);
        int id_e = 2 + i;
        string name_e = "EmployeeName";
        Employee employee(id_e, name_e);
        test_algo.addSkill(skill);
        test_algo.addEmployee(employee);
        test_algo.assignSkill(id_e, id_s, test_level);
        if(i > 0){
            for(int j = 1; j < i; j++){
                test_algo.assignSkill(id_e, id_s - j, test_level - j);
            }
        }
    }

    test_algo.initEffMatrix();
    vector< pair<Employee, Skill> > b_a = (test_algo.getBestAllocation());
    for(int i = 0; i< allocation_size; i++){
        pair<Employee, Skill> *p1 = &(b_a.at(i));
        QVERIFY(p1->first.getId() == p1->second.getId());
    }

}

void Test_BestAllocAlgo::clearContainers()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    BestAllocAlgorithm test_algo;

    test_algo.addSkill(skill);
    test_algo.addEmployee(employee);

    test_algo.assignSkill(id_e, id_s, test_level);
    QVERIFY(test_algo.isSkillExists(id_e, id_s));

    test_algo.clearContainers();
    QVERIFY(!test_algo.isSkillExists(id_e, id_s));
    QVERIFY(test_algo.m_graph.getEdgesCount() == 0);
    QVERIFY(test_algo.m_graph.getUSetSize() == 0);
    QVERIFY(test_algo.m_graph.getVSetSize() == 0);
}
