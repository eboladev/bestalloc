#include "Technology.h"
using namespace bestalloc;

Technology::Technology()
    : m_id(-1), m_name("")
{
}

Technology::Technology(int id, const string& name)
    : m_id(id), m_name(name)
{
}

int Technology::getId() const
{
    return m_id;
}

void Technology::setId(int value)
{
    m_id = value;
}

string Technology::getName() const
{
    return m_name;
}

void Technology::setName(string& value)
{
    m_name = value;
}

Technology::~Technology()
{
}

