// main.cpp
// Author: Edward Ryabikov

#include <QCoreApplication>

#include "BestAllocAlgo.h"
using namespace bestalloc;

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BestAllocAlgorithm algo;
    algo.addEmployee(Employee(1, "Peter"));
    algo.addEmployee(Employee(2, "Mike"));
    algo.addEmployee(Employee(3, "Robby"));
    algo.addEmployee(Employee(4, "James"));
    algo.addEmployee(Employee(5, "Alan"));

    algo.addSkill(Skill(1, "C++"));
    algo.addSkill(Skill(2, "Java"));
    algo.addSkill(Skill(3, "Python"));
    algo.addSkill(Skill(4, "Ruby"));
    algo.addSkill(Skill(5, "Perl"));

    algo.assignSkill(1, 1, 7);
    algo.assignSkill(1, 2, 11);

    algo.assignSkill(2, 2, 4);
    algo.assignSkill(2, 5, 3);

    algo.assignSkill(3, 1, 12);
    algo.assignSkill(3, 3, 6);

    algo.assignSkill(4, 2, 10);
    algo.assignSkill(4, 4, 8);

    algo.assignSkill(5, 4, 4);
    algo.assignSkill(5, 5, 6);

    vector< pair<Employee, Skill> > bestAllocMap = algo.getBestAllocation();

    cout << "Best allocation:" << endl;
    vector< pair<Employee, Skill> >::iterator i;
    for (i = bestAllocMap.begin(); i != bestAllocMap.end(); i++) {
        cout << i->first.getName() << " <---> " << i->second.getName() << endl;
    }

    return 0;
}
