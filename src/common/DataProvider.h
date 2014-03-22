/*! ---------------------------------------------------------------
 * \file   DataProvider.h
 * \brief  DataProvider class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef DATA_PROVIDER_INCLUDED
#define DATA_PROVIDER_INCLUDED

#include "BestAllocAlgo.h"

namespace bestalloc
{
    class DataProvider
    {
    private:
        BestAllocAlgorithm m_algo;

    public:
        DataProvider();

        void addEmployee(const Employee&  employee);
        void addSkill(const Skill& skill);
        void assignSkill(int employeeId, int skillId, int level);

        vector< pair<Employee, Skill> > getBestAllocation();

        void clearContainers();

        ~DataProvider();
    };
}

#endif // DATA_PROVIDER_INCLUDED
