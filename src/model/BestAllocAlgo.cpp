// BestAllocAlgo.cpp
// Implementation of BestAlloc class
// Author: Edward Ryabikov
// version 1.0

#include "BestAllocAlgo.h"
using namespace bestalloc;

#include <algorithm>
#include <limits.h>
#include <iostream>
using namespace std;

BestAllocAlgorithm::BestAllocAlgorithm()
    : m_graph(), m_effMatrix(), m_pairUV(), m_pairVU(),
      m_altTreeUV(), m_altTreeVU(), m_maxRow(), m_minCol()
{
}

const Employee* BestAllocAlgorithm::getEmployeeById(int id)
{
    Bigraph<Employee, Skill>::UIterator i;
    for (i = m_graph.uSetStart(); i != m_graph.uSetEnd(); i++) {
        if (i->getId() == id) return &(*i);
    }

    return NULL;
}

const Skill* BestAllocAlgorithm::getSkillById(int id)
{
    Bigraph<Employee, Skill>::VIterator i;
    for (i = m_graph.vSetStart(); i != m_graph.vSetEnd(); i++) {
        if (i->getId() == id) return &(*i);
    }

    return NULL;
}

bool BestAllocAlgorithm::isSkillExists(int emplId, int skillId)
{
    Bigraph<Employee, Skill>::EdgeIterator i;
    for (i = m_graph.edgesStart(); i != m_graph.edgesEnd(); i++) {
        if (i->getUVertex().getId() == emplId && i->getVVertex().getId() == skillId) {
            return true;
        }
    }

    return false;
}

int BestAllocAlgorithm::getSkillLevel(int emplId, int skillId)
{
    Bigraph<Employee, Skill>::EdgeIterator i;
    for (i = m_graph.edgesStart(); i != m_graph.edgesEnd(); i++) {
        if (i->getUVertex().getId() == emplId && i->getVVertex().getId() == skillId) {
            return i->getWeight();
        }
    }

    return 0;
}

void BestAllocAlgorithm::initEffMatrix()
{
    int n = min(m_graph.getUSetSize(), m_graph.getVSetSize());
    m_effMatrix = vector< vector<int> >(n);
    for (int i = 0; i < n; i++) {
        m_effMatrix[i].assign(n, 0);
    }

    Bigraph<Employee, Skill>::UIterator i;
    for (i = m_graph.uSetStart(); i != m_graph.uSetEnd(); i++) {
        Bigraph<Employee, Skill>::VIterator j;
        for (j = m_graph.vSetStart(); j != m_graph.vSetEnd(); j++) {
            int skillLevel = getSkillLevel(i->getId(), j->getId());
            m_effMatrix[i.getPosition()][j.getPosition()] = skillLevel;
        }
    }
}

bool BestAllocAlgorithm::buildAltTree(int i)
{
    if (m_altTreeUV[i]) return false;

    int n = m_effMatrix.size();

    m_altTreeUV[i] = true;
    for (int j = 0; j < n; j++) {
        if (m_effMatrix[i][j] - m_maxRow[i] - m_minCol[j] == 0) {
            m_altTreeVU[j] = true;
        }
    }

    for (int j = 0; j < n; j++) {
        if (m_effMatrix[i][j] - m_maxRow[i] - m_minCol[j] == 0 && m_pairVU[j] == -1) {
            m_pairUV[i] = j;
            m_pairVU[j] = i;
            return true;
        }
    }

    for (int j = 0; j < n; j++) {
        if (m_effMatrix[i][j] - m_maxRow[i] - m_minCol[j] == 0 && buildAltTree(m_pairVU[j])) {
            m_pairUV[i] = j;
            m_pairVU[j] = i;
            return true;
        }
    }

    return false;
}

void BestAllocAlgorithm::addEmployee(const Employee& employee)
{
    m_graph.addUVertex(employee);
}

void BestAllocAlgorithm::addSkill(const Skill& skill)
{
    m_graph.addVVertex(skill);
}

void BestAllocAlgorithm::assignSkill(int emplId, int techId, int level)
{
    const Employee* targetEmployee = getEmployeeById(emplId);
    const Skill* targetSkill = getSkillById(techId);
    if (targetEmployee != NULL && targetSkill != NULL) {
        bool skillExist = isSkillExists(emplId, techId);
        if (!skillExist) {
            m_graph.addEdge(Edge<Employee, Skill>(*targetEmployee, *targetSkill, level));
        }
    }
}

vector< pair<Employee, Skill> > BestAllocAlgorithm::getBestAllocation()
{
    initEffMatrix();

    int n = m_effMatrix.size();

    m_minCol.assign(n, 0);
    m_maxRow.assign(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m_maxRow[i] = max(m_maxRow[i], m_effMatrix[i][j]);
        }
    }

    m_pairUV.assign (n, -1);
    m_pairVU.assign (n, -1);

    int c = 0;
    while (c < n) {
        m_altTreeUV.assign(n, false);
        m_altTreeVU.assign(n, false);

        int k = 0;
        for (int i = 0; i < n; i++) {
            if (m_pairUV[i] == -1 && buildAltTree(i)) k++;
        }

        c += k;

        if (k == 0) {
            int z = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (m_altTreeUV[i]) {
                    for (int j=0; j<n; ++j) {
                        if (!m_altTreeVU[j]) {
                            z = min(z, m_maxRow[i] + m_minCol[j] - m_effMatrix[i][j]);
                        }
                    }
                }
            }

            for (int i = 0; i < n; i++) {
                if (m_altTreeUV[i]) m_maxRow[i] -= z;
                if (m_altTreeVU[i]) m_minCol[i] += z;
            }
        }
    }

    vector< pair<Employee, Skill> > resultAlloc(n);
    for (int i = 0; i < n; i++) {
        pair<Employee, Skill> allocPair;
        allocPair.first = Employee(*m_graph.uSetItemAt(i));
        allocPair.second = Skill(*m_graph.vSetItemAt(m_pairUV[i]));
        resultAlloc[i] = allocPair;
    }

    return resultAlloc;
}

void BestAllocAlgorithm::clearContainers()
{
    m_graph.clear();
}

BestAllocAlgorithm::~BestAllocAlgorithm()
{
}
