#include "BestAllocAlgo.h"
using namespace bestalloc;

#include <algorithm>
using namespace std;

BestAllocAlgorithm::BestAllocAlgorithm()
    : m_employees(), m_technologies(), m_skillsMap(), m_graph()
{
}

Employee* BestAllocAlgorithm::getEmployeeById(int id)
{
    for (unsigned int i = 0; i < m_employees.size(); i++) {
        if (m_employees[i].getId() == id) return &m_employees[i];
    }

    return NULL;
}

Technology* BestAllocAlgorithm::getTechnologyById(int id)
{
    for (unsigned int i = 0; i < m_technologies.size(); i++) {
        if (m_technologies[i].getId() == id) return &m_technologies[i];
    }

    return NULL;
}

void BestAllocAlgorithm::addEmployee(const Employee& employee)
{
    m_employees.push_back(employee);
    m_graph.addUVertex(employee);
}

void BestAllocAlgorithm::addTechnology(const Technology& technology)
{
    m_technologies.push_back(technology);
    m_graph.addVVertex(technology);
}

void BestAllocAlgorithm::assignSkill(int emplId, int techId, int level)
{
    map< int, list<Skill> >::iterator i = m_skillsMap.find(emplId);
    if (i == m_skillsMap.end()) {
        Employee* targetEmployee = getEmployeeById(emplId);
        Technology* targetTechnology = getTechnologyById(techId);
        if (targetEmployee != NULL && targetTechnology != NULL) {
            list<Skill> skillSet;
            skillSet.push_back(Skill(*targetTechnology, level));
            m_skillsMap[emplId] = skillSet;
        }
    } else {
        list<Skill>::iterator j;
        for (j = i->second.begin(); j != i->second.end(); j++) {
            if (j->getTechnology().getId() == techId) {
                j->setLevel(level);
                break;
            }
        }

        if (j == i->second.end()) {
            Technology* targetTechnology = getTechnologyById(techId);
            if (targetTechnology != NULL) {
                i->second.push_back(Skill(*targetTechnology, level));
            }
        }
    }
}

map<Employee, Skill> BestAllocAlgorithm::getBestAllocation() const
{
    // Stub
    return map<Employee, Skill>();
}

void BestAllocAlgorithm::clearContainers()
{
    m_employees.clear();
    m_technologies.clear();
    m_skillsMap.clear();
    m_graph.clear();
}

BestAllocAlgorithm::~BestAllocAlgorithm()
{
}
