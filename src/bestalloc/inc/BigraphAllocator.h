// BigraphAllocator.h
// Interface and implementation of BigraphAllocator class
// Author: Edward Ryabikov
// version 1.0

#ifndef BIGRAPHALLOCATOR_H_INCLUDED
#define BIGRAPHALLOCATOR_H_INCLUDED

#include "stdlib.h"

#include "Edge.h"

namespace bestalloc
{
    template <class U, class V>
    class BigraphAllocator
    {
    public:
        BigraphAllocator();

        U** allocUSet(U** set, int setSize, int newElemsCount = 1);
        V** allocVSet(V** set, int setSize, int newElemsCount = 1);
        Edge<U, V>** allocEdges(Edge<U, V>** edges, int edgesCount, int newElemsCount = 1);

        void constructUElem(U** set, int position, const U& another);
        void constructVElem(V** set, int position, const V& another);
        void constructEdge(Edge<U, V>** edges, int position, const Edge<U, V>& another);

        void destroyUSet(U** set, int setSize);
        void destroyVSet(V** set, int setSize);
        void destroyEdges(Edge<U, V>** edges, int edgesCount);

        ~BigraphAllocator();
    };

    template <class U, class V>
    BigraphAllocator<U, V>::BigraphAllocator()
    {
    }

    template <class U, class V>
    U** BigraphAllocator<U, V>::allocUSet(U** set, int setSize, int newElemsCount)
    {
        U** resultSet;
        if (set == NULL) {
            resultSet = (U**)malloc(newElemsCount * sizeof(U*));
        } else {
            resultSet = (U**)realloc(set, (setSize + newElemsCount) * sizeof(U*));
        }

        return resultSet;
    }

    template <class U, class V>
    V** BigraphAllocator<U, V>::allocVSet(V** set, int setSize, int newElemsCount)
    {
        V** resultSet;
        if (set == NULL) {
            resultSet = (V**)malloc(newElemsCount * sizeof(V*));
        } else {
            resultSet = (V**)realloc(set, (setSize + newElemsCount) * sizeof(V*));
        }

        return resultSet;
    }

    template <class U, class V>
    Edge<U, V>** BigraphAllocator<U, V>::allocEdges(Edge<U, V>** edges, int edgesCount, int newElemsCount)
    {
        Edge<U, V>** resultEdges;
        if (edges == NULL) {
            resultEdges = (Edge<U, V>**)malloc(newElemsCount * sizeof(Edge<U, V>*));
        } else {
            resultEdges = (Edge<U, V>**)realloc(edges, (edgesCount + newElemsCount) * sizeof(Edge<U, V>*));
        }

        return resultEdges;
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::constructUElem(U** set, int position, const U& another)
    {
        set[position] = new U(another);
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::constructVElem(V** set, int position, const V& another)
    {
        set[position] = new V(another);
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::constructEdge(Edge<U, V>** edges, int position, const Edge<U, V>& another)
    {
        edges[position] = new Edge<U, V>(another);
    }

    template <class U, class V>
    BigraphAllocator<U, V>::~BigraphAllocator()
    {
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::destroyUSet(U** set, int setSize)
    {
        if (set  != NULL) {
            for (int i = 0; i < setSize; i++) {
                delete set[i];
            }

            free(set);
        }
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::destroyVSet(V** set, int setSize)
    {
        if (set  != NULL) {
            for (int i = 0; i < setSize; i++) {
                delete set[i];
            }

            free(set);
        }
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::destroyEdges(Edge<U, V>** edges, int edgesCount)
    {
        if (edges != NULL) {
            for (int i = 0; i < edgesCount; i++) {
                delete edges[i];
            }

            free(edges);
        }
    }
}

#endif // BIGRAPHALLOCATOR_H_INCLUDED
