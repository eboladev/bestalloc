#include <QCoreApplication>

#include "Employee.h"
#include "Bigraph.h"
#include "Edge.h"
#include "BestAllocAlgo.h"
using namespace bestalloc;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Bigraph<int, int> graph;

    Edge<int, int> edge1(1, 2, 3);
    Edge<int, int> edge2(3, 4, 5);
    graph.addEdge(edge1);
    graph.addEdge(edge2);
    graph.addUVertex(2);

    BestAllocAlgorithm algo;
    algo.addEmployee(Employee(1, "Peter"));
    algo.addEmployee(Employee(2, "Mike"));

    algo.addTechnology(Technology(1, "VS 2010"));
    algo.addTechnology(Technology(2, "MS Office"));

    algo.assignSkill(1, 1, 4);
    algo.assignSkill(1, 2, 3);
    algo.assignSkill(2, 1, 3);
    algo.assignSkill(2, 2, 3);

    return a.exec();
}
