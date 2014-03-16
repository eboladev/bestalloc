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

void ProjectSession::addTechnology(const Technology& technology)
{
    m_algo.addTechnology(technology);
}

void ProjectSession::assignSkill(int employeeId, int skillId, int level)
{
    m_algo.assignSkill(employeeId, skillId, level);
}

map<Employee, Skill> ProjectSession::getBestAllocation() const
{
    return m_algo.getBestAllocation();
}

void ProjectSession::clearContainers()
{
    m_algo.clearContainers();
}
