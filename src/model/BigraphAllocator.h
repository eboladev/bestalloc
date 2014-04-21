/*! ---------------------------------------------------------------
 * \file   BigraphAllocator.h
 * \brief  BigraphAllocator template class declaration and implementation
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef BIGRAPHALLOCATOR_H_INCLUDED
#define BIGRAPHALLOCATOR_H_INCLUDED

#include "Edge.h"

#include <QDebug>
#include <time.h>
#include "stdlib.h"

#define POOL_SIZE_LIMIT 100

#define RESIZE_FACTOR_SMALL  0.5
#define RESIZE_FACTOR_MEDIUM 1.0
#define RESIZE_FACTOR_LARGE  1.5

namespace bestalloc
{
    template <class U, class V>
    class BigraphAllocator
    {
    private:
        int m_uSetSizeLimit;
        int m_vSetSizeLimit;
        int m_edgesCountLimit;

        int m_uSetPushCounter;
        int m_uSetReallocCounter;
        struct timespec m_uSetResizeStartTime;
        struct timespec m_uSetResizeEndTime;

        int m_vSetPushCounter;
        int m_vSetReallocCounter;
        struct timespec m_vSetResizeStartTime;
        struct timespec m_vSetResizeEndTime;

        int m_edgesPushCounter;
        int m_edgesReallocCounter;
        struct timespec m_edgesResizeStartTime;
        struct timespec m_edgesResizeEndTime;

    private:
        struct timespec getCurrentTime();
        struct timespec getTimeDiff(struct timespec start, struct timespec end);
        float getResizeFactor(struct timespec frequency, int reallocCounter);

    public:
        BigraphAllocator();

        U** initUSet();
        V** initVSet();
        Edge<U, V>** initEdges();

        U** resizeUSet(U** set, int newSize);
        V** resizeVSet(V** set, int newSize);
        Edge<U, V>** resizeEdges(Edge<U, V>** edges, int newSize);

        void pushUElem(U*** set, int* setSize, const U& elem);
        void pushVElem(V*** set, int* setSize, const V& elem);
        void pushEdge(Edge<U, V>*** edges, int* edgesCount, const Edge<U, V>& edge);

        void destroyUSet(U** set, int setSize);
        void destroyVSet(V** set, int setSize);
        void destroyEdges(Edge<U, V>** edges, int edgesCount);

        ~BigraphAllocator();
    };

    template <class U, class V>
    BigraphAllocator<U, V>::BigraphAllocator()
        : m_uSetSizeLimit(POOL_SIZE_LIMIT),
          m_vSetSizeLimit(POOL_SIZE_LIMIT),
          m_edgesCountLimit(POOL_SIZE_LIMIT),
          m_uSetPushCounter(0), m_uSetReallocCounter(0),
          m_vSetPushCounter(0), m_vSetReallocCounter(0),
          m_edgesPushCounter(0), m_edgesReallocCounter(0)
    {
        m_uSetResizeStartTime.tv_nsec  = 0;
        m_uSetResizeEndTime.tv_nsec    = 0;

        m_vSetResizeStartTime.tv_nsec  = 0;
        m_vSetResizeEndTime.tv_nsec    = 0;

        m_edgesResizeStartTime.tv_nsec = 0;
        m_edgesResizeEndTime.tv_nsec   = 0;
    }

    template <class U, class V>
    struct timespec BigraphAllocator<U, V>::getCurrentTime()
    {
        struct timespec time;
        clockid_t clockType = CLOCK_MONOTONIC;
        clock_gettime(clockType, &time);
        return time;
    }

    template <class U, class V>
    struct timespec BigraphAllocator<U, V>::getTimeDiff(struct timespec start, struct timespec end)
    {
        struct timespec result;
        if ((end.tv_nsec - start.tv_nsec) < 0) {
            result.tv_sec = end.tv_sec - start.tv_sec - 1;
            result.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
        } else {
            result.tv_sec = end.tv_sec - start.tv_sec;
            result.tv_nsec = end.tv_nsec - start.tv_nsec;
        }

        return result;
    }

    template <class U, class V>
    float BigraphAllocator<U, V>::getResizeFactor(timespec frequency, int reallocCounter)
    {
        if (frequency.tv_sec < 1) {
            return 1.0 + RESIZE_FACTOR_LARGE / reallocCounter;;
        } else if (frequency.tv_sec < 10) {
            return 1.0 + RESIZE_FACTOR_MEDIUM / reallocCounter;;
        } else {
            return 1.0 + RESIZE_FACTOR_SMALL / reallocCounter;
        }
    }

    template <class U, class V>
    U** BigraphAllocator<U, V>::initUSet()
    {
        U** resultSet = (U**)malloc(m_uSetSizeLimit * sizeof(U*));
        return resultSet;
    }

    template <class U, class V>
    V** BigraphAllocator<U, V>::initVSet()
    {
        V** resultSet = (V**)malloc(m_vSetSizeLimit * sizeof(V*));
        return resultSet;
    }

    template <class U, class V>
    Edge<U, V>** BigraphAllocator<U, V>::initEdges()
    {
        Edge<U, V>** resultEdges = (Edge<U, V>**)malloc(m_edgesCountLimit * sizeof(Edge<U, V>*));
        return resultEdges;
    }

    template <class U, class V>
    U** BigraphAllocator<U, V>::resizeUSet(U** set, int newSize)
    {
        U** resultSet = (U**)realloc(set, newSize * sizeof(U*));
        return resultSet;
    }

    template <class U, class V>
    V** BigraphAllocator<U, V>::resizeVSet(V** set, int newSize)
    {
        V** resultSet = (V**)realloc(set, newSize * sizeof(V*));
        return resultSet;
    }

    template <class U, class V>
    Edge<U, V>** BigraphAllocator<U, V>::resizeEdges(Edge<U, V>** edges, int newSize)
    {
        Edge<U, V>** resultEdges = (Edge<U, V>**)realloc(edges, newSize * sizeof(Edge<U, V>*));
        return resultEdges;
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::pushUElem(U*** set, int* setSize, const U& elem)
    {
        if (*set == NULL) {
            *set = initUSet();
            m_uSetResizeStartTime = getCurrentTime();
            m_uSetReallocCounter++;
        }

        if (*setSize == m_uSetSizeLimit) {
            m_uSetResizeEndTime = getCurrentTime();
            struct timespec resizeTimeDiff = getTimeDiff(m_uSetResizeStartTime, m_uSetResizeEndTime);

            struct timespec pushFrequency;
            pushFrequency.tv_sec = resizeTimeDiff.tv_sec / m_uSetPushCounter;
            pushFrequency.tv_nsec = resizeTimeDiff.tv_sec % m_uSetPushCounter + resizeTimeDiff.tv_nsec % m_uSetPushCounter;

            float resizeFactor = getResizeFactor(pushFrequency, m_uSetReallocCounter);

            m_uSetSizeLimit *= resizeFactor;
            *set = resizeUSet(*set, m_uSetSizeLimit);
            m_uSetReallocCounter++;
            m_uSetPushCounter = 0;

            m_uSetResizeStartTime = getCurrentTime();
            m_uSetResizeEndTime.tv_sec = 0;
            m_uSetResizeEndTime.tv_nsec = 0;
        }

        (*set)[*setSize] = new U(elem);
        (*setSize)++;

        m_uSetPushCounter++;
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::pushVElem(V*** set, int* setSize, const V& elem)
    {
        if (*set == NULL) {
            *set = initVSet();
            m_vSetResizeStartTime = getCurrentTime();
            m_vSetReallocCounter++;
        }

        if (*setSize == m_vSetSizeLimit) {
            m_vSetResizeEndTime = getCurrentTime();
            struct timespec resizeTimeDiff = getTimeDiff(m_vSetResizeStartTime, m_vSetResizeEndTime);

            struct timespec pushFrequency;
            pushFrequency.tv_sec = resizeTimeDiff.tv_sec / m_vSetPushCounter;
            pushFrequency.tv_nsec = resizeTimeDiff.tv_sec % m_vSetPushCounter + resizeTimeDiff.tv_nsec % m_vSetPushCounter;

            float resizeFactor = getResizeFactor(pushFrequency, m_vSetReallocCounter);

            m_vSetSizeLimit *= resizeFactor;
            *set = resizeVSet(*set, m_vSetSizeLimit);
            m_vSetReallocCounter++;
            m_vSetPushCounter = 0;

            m_vSetResizeStartTime = getCurrentTime();
            m_vSetResizeEndTime.tv_sec = 0;
            m_vSetResizeEndTime.tv_nsec = 0;
        }

        (*set)[*setSize] = new V(elem);
        (*setSize)++;

        m_vSetPushCounter++;
    }

    template <class U, class V>
    void BigraphAllocator<U, V>::pushEdge(Edge<U, V>*** edges, int* edgesCount, const Edge<U, V>& another)
    {
        if (*edges == NULL) {
            *edges = initEdges();
            m_edgesResizeStartTime = getCurrentTime();
            m_edgesReallocCounter++;
        }

        if (*edgesCount == m_edgesCountLimit) {
            m_edgesResizeEndTime = getCurrentTime();
            struct timespec resizeTimeDiff = getTimeDiff(m_edgesResizeStartTime, m_edgesResizeEndTime);

            struct timespec pushFrequency;
            pushFrequency.tv_sec = resizeTimeDiff.tv_sec / m_edgesPushCounter;
            pushFrequency.tv_nsec = resizeTimeDiff.tv_sec % m_edgesPushCounter + resizeTimeDiff.tv_nsec % m_edgesPushCounter;

            float resizeFactor = getResizeFactor(pushFrequency, m_edgesReallocCounter);

            qDebug() << "===============";
            qDebug() << "realloc cntr = " << m_edgesReallocCounter;
            qDebug() << "resize diff = " << resizeTimeDiff.tv_sec << "s " << resizeTimeDiff.tv_nsec << "ns";
            qDebug() << "resize factor = " << resizeFactor;
            qDebug() << "count limit = " << m_edgesCountLimit;


            m_edgesCountLimit *= resizeFactor;
            *edges = resizeEdges(*edges, m_edgesCountLimit);
            m_edgesReallocCounter++;
            m_edgesPushCounter = 0;
            qDebug() << "count limit = " << m_edgesCountLimit;

            m_edgesResizeStartTime = getCurrentTime();
            m_edgesResizeEndTime.tv_sec = 0;
            m_edgesResizeEndTime.tv_nsec = 0;
        }

        (*edges)[*edgesCount] = new Edge<U, V>(another);
        (*edgesCount)++;

        m_edgesPushCounter++;
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

        m_uSetSizeLimit = POOL_SIZE_LIMIT;
        m_uSetPushCounter = 0;
        m_uSetReallocCounter = 0;

        m_uSetResizeStartTime.tv_nsec = 0;
        m_uSetResizeEndTime.tv_nsec   = 0;
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

        m_vSetSizeLimit = POOL_SIZE_LIMIT;
        m_vSetPushCounter = 0;
        m_vSetReallocCounter = 0;

        m_vSetResizeStartTime.tv_nsec  = 0;
        m_vSetResizeEndTime.tv_nsec    = 0;
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

        m_edgesCountLimit = POOL_SIZE_LIMIT;
        m_edgesPushCounter = 0;
        m_edgesReallocCounter = 0;

        m_edgesResizeStartTime.tv_nsec = 0;
        m_edgesResizeEndTime.tv_nsec   = 0;
    }

    template <class U, class V>
    BigraphAllocator<U, V>::~BigraphAllocator()
    {
    }
}

#endif // BIGRAPHALLOCATOR_H_INCLUDED
