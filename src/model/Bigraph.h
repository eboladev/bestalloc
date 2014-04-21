/*! ---------------------------------------------------------------
 * \file   Bigraph.h
 * \brief  Bigraph template class declaration and implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef BIGRAPH_H_INCLUDED
#define BIGRAPH_H_INCLUDED

#include "Edge.h"
#include "BigraphIterator.h"
#include "BigraphAllocator.h"

namespace bestalloc
{
    template < class U, class V, class A = BigraphAllocator<U, V> >
    class Bigraph
    {
    private:
        U**          m_uSet;
        V**          m_vSet;
        Edge<U, V>** m_edges;
        int          m_uSetSize;
        int          m_vSetSize;
        int          m_edgesCount;

        A            m_allocator;

    public:
        Bigraph(const A& allocator = A());

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

    template <class U, class V, class A>
    Bigraph<U, V, A>::Bigraph(const A& allocator)
        : m_uSet(NULL), m_vSet(NULL), m_edges(NULL),
          m_uSetSize(0), m_vSetSize(0), m_edgesCount(0),
          m_allocator(allocator)
    {
    }

    template <class U, class V, class A>
    int Bigraph<U, V, A>::getUSetSize() const
    {
        return m_uSetSize;
    }

    template <class U, class V, class A>
    int Bigraph<U, V, A>::getVSetSize() const
    {
        return m_vSetSize;
    }

    template <class U, class V, class A>
    int Bigraph<U, V, A>::getEdgesCount() const
    {
        return m_edgesCount;
    }

    template <class U, class V, class A>
    void Bigraph<U, V, A>::addEdge(const Edge<U, V>& edge)
    {
        m_allocator.pushEdge(&m_edges, &m_edgesCount, edge);
    }

    template <class U, class V, class A>
    void Bigraph<U, V, A>::addUVertex(const U& vertex)
    {
        m_allocator.pushUElem(&m_uSet, &m_uSetSize, vertex);
    }

    template <class U, class V, class A>
    void Bigraph<U, V, A>::addVVertex(const V& vertex)
    {
        m_allocator.pushVElem(&m_vSet, &m_vSetSize, vertex);
    }

    template <class U, class V, class A>
    void Bigraph<U, V, A>::clear()
    {
        m_allocator.destroyUSet(m_uSet, m_uSetSize);
        m_uSet = NULL;
        m_uSetSize = 0;

        m_allocator.destroyVSet(m_vSet, m_vSetSize);
        m_vSet = NULL;
        m_vSetSize = 0;

        m_allocator.destroyEdges(m_edges, m_edgesCount);
        m_edges = NULL;
        m_edgesCount = 0;
    }

    template <class U, class V, class A>
    BigraphIterator<U> Bigraph<U, V, A>::uSetStart()
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, 0);
    }

    template <class U, class V, class A>
    BigraphIterator<U> Bigraph<U, V, A>::uSetItemAt(int position)
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, position);
    }

    template <class U, class V, class A>
    BigraphIterator<U> Bigraph<U, V, A>::uSetEnd()
    {
        return BigraphIterator<U>(m_uSet, m_uSetSize, m_uSetSize);
    }

    template <class U, class V, class A>
    BigraphIterator<V> Bigraph<U, V, A>::vSetStart()
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, 0);
    }

    template <class U, class V, class A>
    BigraphIterator<V> Bigraph<U, V, A>::vSetItemAt(int position)
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, position);
    }

    template <class U, class V, class A>
    BigraphIterator<V> Bigraph<U, V, A>::vSetEnd()
    {
        return BigraphIterator<V>(m_vSet, m_vSetSize, m_vSetSize);
    }

    template <class U, class V, class A>
    BigraphIterator< Edge<U, V> > Bigraph<U, V, A>::edgesStart()
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, 0);
    }

    template <class U, class V, class A>
    BigraphIterator< Edge<U, V> > Bigraph<U, V, A>::edgesItemAt(int position)
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, position);
    }

    template <class U, class V, class A>
    BigraphIterator< Edge<U, V> > Bigraph<U, V, A>::edgesEnd()
    {
        return BigraphIterator< Edge<U, V> >(m_edges, m_edgesCount, m_edgesCount);
    }

    template <class U, class V, class A>
    Bigraph<U, V, A>::~Bigraph()
    {
        clear();
    }

}

#endif // BIGRAPH_H_INCLUDED
