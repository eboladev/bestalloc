#ifndef PROJECT_SESSION
#define PROJECT_SESSION

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
        void addTechnology(const Technology& technology);
        void assignSkill(int employeeId, int skillId, int level);

        map<Employee, Skill> getBestAllocation() const;

        void clearContainers();
    };
}

#endif // PROJECT_SESSION
