// Edge.h
// Interface and implementation of Edge template class
// Author: Edward Ryabikov
// version 1.0

#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

namespace bestalloc
{
    template <class U, class V>
    class Edge
    {
    private:
        U   m_uVertex;
        V   m_vVertex;
        int m_weight;

    public:
        Edge();
        Edge(const Edge& edge);
        Edge(const U& uVertex, const V& vVertex, int weight);

        void setUVertex(const U& value);
        U    getUVertex() const;
        void setVVertex(const V& value);
        V    getVVertex() const;
        void setWeight(int value);
        int  getWeight() const;

        ~Edge();
    };

    template <class U, class V>
    Edge<U, V>::Edge()
        : m_uVertex(), m_vVertex(), m_weight(0)
    {
    }

    template <class U, class V>
    Edge<U, V>::Edge(const Edge &edge)
        : m_uVertex(edge.getUVertex()), m_vVertex(edge.getVVertex()), m_weight(edge.getWeight())
    {

    }

    template <class U, class V>
    Edge<U, V>::Edge(const U& uVertex, const V& vVertex, int weight)
        : m_uVertex(uVertex), m_vVertex(vVertex), m_weight(weight)
    {
    }

    template <class U, class V>
    void Edge<U, V>::setUVertex(const U& value)
    {
        m_uVertex = value;
    }

    template <class U, class V>
    U Edge<U, V>::getUVertex() const
    {
        return m_uVertex;
    }

    template <class U, class V>
    void Edge<U, V>::setVVertex(const V& value)
    {
        m_vVertex = value;
    }

    template <class U, class V>
    V Edge<U, V>::getVVertex() const
    {
        return m_vVertex;
    }

    template <class U, class V>
    void Edge<U, V>::setWeight(int value)
    {
        m_weight = value;
    }

    template <class U, class V>
    int Edge<U, V>::getWeight() const
    {
        return m_weight;
    }

    template <class U, class V>
    Edge<U, V>::~Edge()
    {
    }
}

#endif // EDGE_H_INCLUDED
