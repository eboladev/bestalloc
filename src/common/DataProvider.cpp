/*! ---------------------------------------------------------------
 * \file   DataProvider.cpp
 * \brief  DataProvider class implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#include "DataProvider.h"
using namespace bestalloc;

DataProvider::DataProvider(const BestAllocAlgorithm& algo)
    : m_algo(algo)
{
}

void DataProvider::addEmployee(const Employee &employee)
{
    m_algo.addEmployee(employee);
}

void DataProvider::addSkill(const Skill& skill)
{
    m_algo.addSkill(skill);
}

void DataProvider::assignSkill(int employeeId, int skillId, int level)
{
    m_algo.assignSkill(employeeId, skillId, level);
}

vector< pair<Employee, Skill> > DataProvider::getBestAllocation()
{
    return m_algo.getBestAllocation();
}

void DataProvider::clearContainers()
{
    m_algo.clearContainers();
}

DataProvider::~DataProvider()
{
}
