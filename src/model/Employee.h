// Employee.h
// Interface of Employee class
// Author: Edward Ryabikov
// version 1.0

#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include "Skill.h"

#include <string>
#include <vector>
using namespace std;

namespace bestalloc
{
    class Employee
    {
    private:
        int    m_id;
        string m_name;

    public:
        Employee();
        Employee(int id, const string& name);

        int    getId() const;
        void   setId(int value);
        string getName() const;
        void   setName(string& value);

        ~Employee();
    };
}

#endif // EMPLOYEE_H_INCLUDED

