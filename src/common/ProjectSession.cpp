// ProjectSession.cpp
// Implementation of ProjectSession class
// Edward Ryabikov
// version 1.0

#include "ProjectSession.h"
using namespace bestalloc;

ProjectSession* ProjectSession::m_instance = NULL;

ProjectSession::ProjectSession()
    : m_algo()
{
}

ProjectSession* ProjectSession::getInstance()
{
    if (m_instance == NULL) {
        m_instance = new ProjectSession();
    }

    return m_instance;
}

void ProjectSession::addEmployee(const Employee &employee)
{
    m_algo.addEmployee(employee);
}

void ProjectSession::addSkill(const Skill& skill)
{
    m_algo.addSkill(skill);
}

void ProjectSession::assignSkill(int employeeId, int skillId, int level)
{
    m_algo.assignSkill(employeeId, skillId, level);
}

vector< pair<Employee, Skill> > ProjectSession::getBestAllocation()
{
    return m_algo.getBestAllocation();
}

void ProjectSession::clearContainers()
{
    m_algo.clearContainers();
}
