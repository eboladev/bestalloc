#ifndef BESTALLOCALGO_H
#define BESTALLOCALGO_H

#include "Bigraph.h"
#include "Employee.h"
#include "Skill.h"

#include <map>
#include <vector>
#include <list>
using namespace std;

namespace bestalloc
{
    class BestAllocAlgorithm
    {
    private:
        vector<Employee>         m_employees;
        vector<Technology>       m_technologies;
        map< int, list<Skill> >  m_skillsMap;
        Bigraph<Employee, Technology> m_graph;

    private:
        Employee*   getEmployeeById(int id);
        Technology* getTechnologyById(int id);

    public:
        BestAllocAlgorithm();

        void addEmployee(const Employee& employee);
        void addTechnology(const Technology& technology);
        void assignSkill(int emplId, int techId, int level);

        map<Employee, Skill> getBestAllocation() const;

        void clearContainers();

        ~BestAllocAlgorithm();
    };
}

#endif // BESTALLOCALGO_H
