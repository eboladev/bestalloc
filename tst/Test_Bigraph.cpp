/*! ---------------------------------------------------------------
 * \file   Test_Bigraph.cpp
 * \brief  Test suite for Bigraph class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#include "Test_Bigraph.h"
using namespace test;
using namespace bestalloc;;

Test_Bigraph::Test_Bigraph()
{
}

void  Test_Bigraph::getUSetSize()
{
    Bigraph<int, float> graph;
    QVERIFY(graph.getUSetSize() == 0);
    int a = 1;
    graph.addUVertex(a);
    QVERIFY(graph.getUSetSize() == 1);
}

void Test_Bigraph::getVSetSize()
{
    Bigraph<int, float> graph;
    QVERIFY(graph.getVSetSize() == 0);
    float a = 1.0f;
    graph.addVVertex(a);
    QVERIFY(graph.getVSetSize() == 1);
}

void  Test_Bigraph::getEdgesCount()
{
    Bigraph<int, float> graph;
    QVERIFY(graph.getEdgesCount() == 0);
    int a = 1;
    float b = 1.0f;
    graph.addUVertex(a);
    graph.addVVertex(b);
    Edge<int, float> edge(a, b, 10);
    graph.addEdge(edge);
    QVERIFY(graph.getEdgesCount() == 1);
}

void Test_Bigraph::addEdge()
{
    Bigraph<int, float> graph;
    int a = 1;
    float b = 1.5f;
    int weight = 10;
    graph.addUVertex(a);
    graph.addVVertex(b);
    Edge<int, float> edge(a, b, weight);
    graph.addEdge(edge);
    BigraphIterator< Edge<int, float> > i = graph.edgesStart();
    QVERIFY(i->getUVertex() == a);
    QVERIFY(i->getVVertex() == b);
    QVERIFY(i->getWeight() == weight);
}

void Test_Bigraph::addUVertex()
{
    Bigraph<int, float> graph;
    int a = 1;
    graph.addUVertex(a);
    BigraphIterator< int > i = graph.uSetStart();
    QVERIFY(*i == a);
}

void Test_Bigraph::addVVertex()
{
    Bigraph<int, float> graph;
    float b = 1.5f;
    graph.addVVertex(b);
    BigraphIterator< float > i = graph.vSetStart();
    QVERIFY(*i == b);
}

void Test_Bigraph::clear()
{
    Bigraph<int, float> graph;
    int a = 1;
    float b = 1.5f;
    int weight = 10;
    graph.addUVertex(a);
    graph.addVVertex(b);
    Edge<int, float> edge(a, b, weight);
    graph.addEdge(edge);
    graph.clear();
    QVERIFY(graph.getEdgesCount() == 0);
    QVERIFY(graph.getUSetSize() == 0);
    QVERIFY(graph.getVSetSize() == 0);
    BigraphIterator< Edge<int, float> > i = graph.edgesStart();
    BigraphIterator< int > j = graph.uSetStart();
    BigraphIterator< float > k = graph.vSetStart();
    QVERIFY(!(i->getUVertex() == a));
    QVERIFY(!(i->getVVertex() == b));
    QVERIFY(!(*j == a));
    QVERIFY(!(*k == b));
}

void Test_Bigraph::uSetStart()
{
    Bigraph<int, float> graph;
    int a = 1;
    graph.addUVertex(a);
    a++;
    graph.addUVertex(a);
    BigraphIterator< int > i = graph.uSetStart();
    QVERIFY(i.getPosition() == 0);
    QVERIFY(*i == a - 1);
}

void Test_Bigraph::uSetItemAt()
{
    Bigraph<int, float> graph;
    int a = 1;
    int position = 1;
    graph.addUVertex(a);
    a++;
    graph.addUVertex(a);
    BigraphIterator< int > i = graph.uSetItemAt(position);
    QVERIFY(i.getPosition() == position);
    QVERIFY(*i == a);
}

void Test_Bigraph::uSetEnd()
{
    Bigraph<int, float> graph;
    int a_start = 1;
    int a = a_start;
    int length = 3;
    for(int j = 0; j< length; j++){
        graph.addUVertex(a);
        a++;
    }
    BigraphIterator< int > i = graph.uSetEnd();
    --i;
    int j = length - 1;
    a = a_start + length - 1;
    while(j >= 0){
        QVERIFY(i.getPosition() == j);
        QVERIFY(*i == a);
        --a;
        --i;
        --j;
    }
}

void Test_Bigraph::vSetStart()
{
    Bigraph<int, float> graph;
    float a = 1.5f;
    graph.addVVertex(a);
    a += 1.0f;
    graph.addVVertex(a);
    BigraphIterator< float > i = graph.vSetStart();
    QVERIFY(i.getPosition() == 0);
    QVERIFY(*i == a - 1.0f);
}

void Test_Bigraph::vSetItemAt()
{
    Bigraph<int, float> graph;
    float a = 1.5f;
    int position = 1;
    graph.addVVertex(a);
    a += 1.0f;
    graph.addVVertex(a);
    BigraphIterator< float > i = graph.vSetItemAt(position);
    QVERIFY(i.getPosition() == position);
    QVERIFY(*i == a);
}

void Test_Bigraph::vSetEnd()
{
    Bigraph<int, float> graph;
    float a_start = 1.0f;
    float a_stride = 1.0f;
    float a = a_start;
    int length = 3;
    for(int j = 0; j< length; j++){
        graph.addVVertex(a);
        a += a_stride;
    }
    BigraphIterator< float > i = graph.vSetEnd();
    --i;
    int j = length - 1;
    a = a_start + (length - 1) * a_stride;
    while(j >= 0){
        QVERIFY(i.getPosition() == j);
        QVERIFY(*i == a);
        a -= a_stride;
        --i;
        --j;
    }
}

void Test_Bigraph::edgesItemAt()
{
    Bigraph<int, float> graph;
    int a = 1;
    float b = 1.5f;
    int weight = 10;
    int position = 1;
    graph.addVVertex(b);
    for(int i = 0; i <=position; i++){
        graph.addUVertex(a);
        Edge<int, float> edge(a, b, weight);
        a++;
        graph.addEdge(edge);
    }
    BigraphIterator< Edge<int, float> > i = graph.edgesItemAt(position);
    QVERIFY(i->getUVertex() == --a);
    QVERIFY(i->getVVertex() == b);
    QVERIFY(i->getWeight() == weight);
    QVERIFY(i.getPosition() == position);
}

void Test_Bigraph::edgesStart()
{
    Bigraph<int, float> graph;
    int a = 1;
    float b = 1.5f;
    int weight = 10;
    graph.addUVertex(a);
    graph.addVVertex(b);
    Edge<int, float> edge(a, b, weight);
    graph.addEdge(edge);
    a++;
    Edge<int, float> edge1(a, b, weight);
    graph.addEdge(edge1);
    BigraphIterator< Edge<int, float> > i = graph.edgesStart();
    QVERIFY(i->getUVertex() == --a);
    QVERIFY(i->getVVertex() == b);
    QVERIFY(i->getWeight() == weight);
    QVERIFY(i.getPosition() == 0);
}

void Test_Bigraph::edgesEnd()
{
    Bigraph<int, float> graph;
    int a_start = 1;
    int a_stride = 3;
    int a = a_start;
    float b_start = 1.0f;
    float b_stride = 2.0f;
    float b = b_start;
    int weight = 10;
    int length = 10;
    for(int j = 0; j< length; j++){
        graph.addVVertex(b);
        graph.addUVertex(a);
        Edge<int, float> edge(a, b, weight);
        graph.addEdge(edge);
        a += a_stride;
        b += b_stride;
    }
    BigraphIterator< Edge<int, float> > i = graph.edgesEnd();
    --i;
    int j = length - 1;
    a = a_start + (length - 1) * a_stride;
    b = b_start + (length - 1) * b_stride;
    while(j >= 0){
        QVERIFY(i.getPosition() == j);
        QVERIFY(i->getUVertex() == a);
        QVERIFY(i->getVVertex() == b);
        QVERIFY(i->getWeight() == weight);
        a -= a_stride;
        b -= b_stride;
        --i;
        --j;
    }
}
