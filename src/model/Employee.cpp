/*! ---------------------------------------------------------------
 * \file   Employee.cpp
 * \brief  Employee class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "Employee.h"
#include "ConfigReader.h"
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

void Employee::save(QDataStream &str)
{
    str<<(qint32)m_id;
    str<<m_name.data();
}

void Employee::load(QDataStream &str)
{
    str>>m_id;
    m_name = ConfigReader::readString(str);
}
