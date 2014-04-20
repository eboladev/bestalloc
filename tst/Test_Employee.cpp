/*! ---------------------------------------------------------------
 * \file   Test_Employee.cpp
 * \brief  Test suite for Employee class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "Test_Employee.h"

#include "Employee.h"
using namespace bestalloc;
using namespace test;

Test_Employee::Test_Employee()
{

}

void Test_Employee::getId()
{
    int id = 2;
    string name = "EmployeeName";

    Employee employee(id, name);

    QVERIFY(employee.getId() == id);
}

void Test_Employee::setId()
{
    Employee employee;

    int id = 2;
    employee.setId(id);

    QVERIFY(employee.getId() == id);
}

void Test_Employee::getName()
{
    int id = 2;
    string name = "EmployeeName";

    Employee employee(id, name);

    QVERIFY(employee.getName() == name);
}

void Test_Employee::setName()
{
    Employee employee;

    string name = "EmployeeName";
    employee.setName(name);

    QVERIFY(employee.getName() == name);
}
