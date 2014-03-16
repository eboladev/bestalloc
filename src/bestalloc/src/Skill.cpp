#include "Skill.h"
using namespace bestalloc;

Skill::Skill()
    : m_technology(), m_level(0)
{
}

Skill::Skill(const Technology& technology, int level)
    : m_technology(technology), m_level(level)
{
}

Technology Skill::getTechnology() const
{
    return m_technology;
}

void Skill::setTechnology(const Technology& value)
{
    m_technology = value;
}

int Skill::getLevel() const
{
    return m_level;
}

void Skill::setLevel(int value)
{
    m_level = value;
}

Skill::~Skill()
{
}
