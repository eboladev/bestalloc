// ProjectSession.h
// Interface of ProjectSession class
// Author: Edward Ryabikov
// version 1.0

#ifndef PROJECT_SESSION_INCLUDED
#define PROJECT_SESSION_INCLUDED

#include "BestAllocAlgo.h"

#include <map>
using namespace std;

namespace bestalloc
{
    class ProjectSession {
    private:
        static ProjectSession* m_instance;
        BestAllocAlgorithm     m_algo;

    private:
        ProjectSession();
        ~ProjectSession();

    public:
        static ProjectSession* getInstance();

        void addEmployee(const Employee&  employee);
        void addSkill(const Skill& skill);
        void assignSkill(int employeeId, int skillId, int level);

        vector< pair<Employee, Skill> > getBestAllocation();

        void clearContainers();
    };
}

#endif // PROJECT_SESSION_INCLUDED
