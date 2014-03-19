/*! ---------------------------------------------------------------
 * \file   Skill.cpp
 * \brief  Skill class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "Skill.h"
using namespace bestalloc;

Skill::Skill()
    : m_id(-1), m_name("")
{
}

Skill::Skill(int id, const string& name)
    : m_id(id), m_name(name)
{
}

int Skill::getId() const
{
    return m_id;
}

void Skill::setId(int value)
{
    m_id = value;
}

string Skill::getName() const
{
    return m_name;
}

void Skill::setName(string& value)
{
    m_name = value;
}

Skill::~Skill()
{
}
