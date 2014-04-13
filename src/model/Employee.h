/*! ---------------------------------------------------------------
 * \file   Employee.h
 * \brief  Employee class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include <QDataStream>

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

        void save(QDataStream &str);
        void load(QDataStream &str);
    };
}

#endif // EMPLOYEE_H_INCLUDED

