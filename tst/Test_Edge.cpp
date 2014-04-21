/*! ---------------------------------------------------------------
 * \file   Test_Edge.cpp
 * \brief  Test suite for Edge class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "Test_Edge.h"

#include "Edge.h"
#include "Skill.h"
#include "Employee.h"
using namespace bestalloc;
using namespace test;

Test_Edge::Test_Edge()
{
}

void Test_Edge::setUVertex()
{
    int id_e = 2;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    Edge<Employee, Skill> test_edge;
    test_edge.setUVertex(employee);
    QVERIFY(test_edge.getUVertex().getId() == id_e);
    QVERIFY(test_edge.getUVertex().getName() == name_e);
}

void Test_Edge::getUVertex()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 3;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    Edge<Employee, Skill> test_edge(employee, skill, test_level);
    QVERIFY(test_edge.getUVertex().getId() == id_e);
    QVERIFY(test_edge.getUVertex().getName() == name_e);
}

void Test_Edge::setVVertex()
{
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);

    Edge<Employee, Skill> test_edge;
    test_edge.setVVertex(skill);
    QVERIFY(test_edge.getVVertex().getId() == id_s);
    QVERIFY(test_edge.getVVertex().getName() == name_s);
}

void Test_Edge::getVVertex()
{
    int test_level = 1;
    int id_s = 2;
    string name_s = "SKillName";
    Skill skill(id_s, name_s);
    int id_e = 3;
    string name_e = "EmployeeName";
    Employee employee(id_e, name_e);

    Edge<Employee, Skill> test_edge(employee, skill, test_level);
    QVERIFY(test_edge.getVVertex().getId() == id_s);
    QVERIFY(test_edge.getVVertex().getName() == name_s);
}

void Test_Edge::setWeight()
{
    int test_weight = 1;

    Edge<Employee, Skill> test_edge;
    test_edge.setWeight(test_weight);
    QVERIFY(test_edge.getWeight() == test_weight);
}

void Test_Edge::getWeight()
{
        int test_weight = 1;
        int id_s = 2;
        string name_s = "SKillName";
        Skill skill(id_s, name_s);
        int id_e = 3;
        string name_e = "EmployeeName";
        Employee employee(id_e, name_e);

        Edge<Employee, Skill> test_edge(employee, skill, test_weight);
        QVERIFY(test_edge.getWeight() == test_weight);
}
