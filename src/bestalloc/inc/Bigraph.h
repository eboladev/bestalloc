// Bigraph.h
// Interface and implementation of Bigraph template class
// Author: Edward Ryabikov
// version 1.0

#ifndef BIGRAPH_H_INCLUDED
#define BIGRAPH_H_INCLUDED

#include <stdlib.h>

#include "Edge.h"
#include "BigraphIterator.h"

namespace bestalloc
{
    template <class U, class V>
    class Bigraph
    {
    private:
        U**          m_uSet;
        V**          m_vSet;
        Edge<U, V>** m_edges;
        int          m_uSetSize;
        int          m_vSetSize;
        int          m_edgesCount;

    public:
        Bigraph();

        int  getUSetSize() const;
        int  getVSetSize() const;
        int  getEdgesCount() const;

        void addEdge(const Edge<U,V>& edge);
        void addUVertex(const U& vertex);
        void addVVertex(const V& vertex);

        void clear();

        typedef BigraphIterator<U> UIterator;
        BigraphIterator<U> uSetStart();
        BigraphIterator<U> uSetItemAt(int position);
        BigraphIterator<U> uSetEnd();

        typedef BigraphIterator<V> VIterator;
        BigraphIterator<V> vSetStart();
        BigraphIterator<V> vSetItemAt(int position);
        BigraphIterator<V> vSetEnd();

        typedef BigraphIterator< Edge<U, V> > EdgeIterator;
        BigraphIterator< Edge<U, V> > edgesStart();
        BigraphIterator< Edge<U, V> > edgesItemAt(int position);
        BigraphIterator< Edge<U, V> > edgesEnd();

        ~Bigraph();
    };

    template <class U, class V>
    Bigraph<U, V>::Bigraph()
        : m_uSet(NULL), m_vSet(NULL), m_edges(NULL),
          m_uSetSize(0), m_vSetSize(0), m_edgesCount(0)
    {
    }

    template <class U, class V>
    int Bigraph<U, V>::getUSetSize() const
    {
        return m_uSetSize;
    }

    template <class U, class V>
    int Bigraph<U, V>::getVSetSize() const
    {
        return m_vSetSize;
    }

    template <class U, class V>
    int Bigraph<U, V>::getEdgesCount() const
    {
        return m_edgesCount;
    }

    template <class U, class V>
    void Bigraph<U, V>::addEdge(const Edge<U, V>& edge)
    {
        if (m_edges == NULL) {
            m_edges = (Edge<U, V>**)malloc(sizeof(Edge<U, V>*));
        } else {
            m_edges = (Edge<U, V>**)realloc(m_edges, (m_edgesCount+1) * sizeof(Edge<U, V>*));
        }

        m_edges[m_edgesCount] = new Edge<U, V>(edge);
        m_edgesCount++;
    }

    template <class U, class V>
    void Bigraph<U, V>::addUVertex(const U& vertex)
    {
        if (m_uSet == NULL) {
            m_uSet = (U**)malloc(sizeof(U*));
        } else {
            m_uSet = (U**)realloc(m_uSet, (m_uSetSize+1) * sizeof(U*));
        }

        m_uSet[m_uSetSize] = new U(vertex);
        m_uSetSize++;
    }

    template <class U, class V>
    void Bigraph<U, V>::addVVertex(const V& vertex)
    {
        if (m_vSet == NULL) {
            m_vSet = (V**)malloc(sizeof(V*));
        } else {
            m_vSet = (V**)realloc(m_vSet, (m_vSetSize+1) * sizeof(V*));
        }

        m_vSet[m_vSetSize] = new V(vertex);
        m_vSetSize++;
    }

    template <class U, class V>
    void Bigraph<U, V>::clear()
    {
        if (m_edges != NULL) {
            for (int i = 0; i < m_edgesCount; i++) {
                delete m_edges[i];
            }

            free(m_edges);
            m_edges = NULL;
            m_edgesCount = 0;
        }

        if (m_uSet  != NULL) {
            for (int i = 0; i < m_uSetSize; i++) {
                delete m_uSet[i];
            }

            free(m_uSet);
            m_uSet = NULL;
            m_uSetSize = 0;
        }

        if (m_vSet  != NULL) {
            for (int i = 0; i < m_vSetSize; i++) {
                delete m_vSet[i];
            }

            free(m_vSet);
            m_vSet = NULL;
            m_vSetSize = 0;
        }
    }

    template <class U, class V>
    BigraphIterator<U> Bigraph<U, V>::uSetStart()
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, 0);
    }

    template <class U, class V>
    BigraphIterator<U> Bigraph<U, V>::uSetItemAt(int position)
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, position);
    }

    template <class U, class V>
    BigraphIterator<U> Bigraph<U, V>::uSetEnd()
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, m_uSetSize);
    }

    template <class U, class V>
    BigraphIterator<V> Bigraph<U, V>::vSetStart()
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, 0);
    }

    template <class U, class V>
    BigraphIterator<V> Bigraph<U, V>::vSetItemAt(int position)
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, position);
    }

    template <class U, class V>
    BigraphIterator<V> Bigraph<U, V>::vSetEnd()
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, m_vSetSize);
    }

    template <class U, class V>
    BigraphIterator< Edge<U, V> > Bigraph<U, V>::edgesStart()
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, 0);
    }

    template <class U, class V>
    BigraphIterator< Edge<U, V> > Bigraph<U, V>::edgesItemAt(int position)
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, position);
    }

    template <class U, class V>
    BigraphIterator< Edge<U, V> > Bigraph<U, V>::edgesEnd()
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, m_edgesCount);
    }

    template <class U, class V>
    Bigraph<U, V>::~Bigraph()
    {
        clear();
    }
}

#endif // BIGRAPH_H_INCLUDED
