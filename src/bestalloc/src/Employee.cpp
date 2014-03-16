#include "Employee.h"
using namespace bestalloc;

Employee::Employee()
    : m_id(-1), m_name("")
{
}

Employee::Employee(int id, const string& name)
    : m_id(id), m_name(name)
{
}

int Employee::getId() const
{
    return m_id;
}

void Employee::setId(int value)
{
    m_id = value;
}

string Employee::getName() const
{
    return m_name;
}

void Employee::setName(string &value)
{
    m_name = value;
}

Employee::~Employee()
{
}
