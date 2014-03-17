// BigraphIterator.h
// Interface and implementation of BigraphIterator class
// Author: Edward Ryabikov
// version 1.0

#ifndef BIGRAPHITERATOR_H_INCLUDED
#define BIGRAPHITERATOR_H_INCLUDED

namespace bestalloc
{
    template <class T>
    class BigraphIterator
    {
    private:
        T** m_targetSet;
        int m_size;
        int m_position;
        T   m_emptyValue;

    public:
        BigraphIterator();
        BigraphIterator(T** targetSet, int size);
        BigraphIterator(T** targetSet, int size, int curPosition);

        int getPosition() const;

        const BigraphIterator<T>& operator=(const BigraphIterator<T>& another);
        bool operator==(const BigraphIterator<T>& another);
        bool operator!=(const BigraphIterator<T>& another);
        BigraphIterator<T>& operator++();
        BigraphIterator<T>& operator++(int);
        BigraphIterator<T>& operator--();
        const T* operator->() const;
        const T& operator*() const;

        ~BigraphIterator();
    };

    template <class T>
    BigraphIterator<T>::BigraphIterator()
        : m_targetSet(NULL), m_size(0), m_position(-1), m_emptyValue()
    {
    }

    template <class T>
    BigraphIterator<T>::BigraphIterator(T** targetSet, int size)
        : m_targetSet(targetSet), m_size(size), m_position(-1), m_emptyValue()
    {
    }

    template <class T>
    BigraphIterator<T>::BigraphIterator(T** targetSet, int size, int curPosition)
        : m_targetSet(targetSet), m_size(size), m_position(curPosition), m_emptyValue()
    {
    }

    template <class T>
    int BigraphIterator<T>::getPosition() const
    {
        return m_position;
    }

    template <class T>
    const BigraphIterator<T>& BigraphIterator<T>::operator=(const BigraphIterator<T>& another)
    {
        m_targetSet = another.m_targetSet;
        m_size = another.m_size;
        m_position = another.m_position;

        return *this;
    }

    template <class T>
    bool BigraphIterator<T>::operator==(const BigraphIterator<T>& another)
    {
        bool isEqual = (m_targetSet == another.m_targetSet &&
                        m_size == another.m_size &&
                        m_position == another.m_position);

        return isEqual;
    }

    template <class T>
    bool BigraphIterator<T>::operator!=(const BigraphIterator<T>& another)
    {
        bool isEqual = (m_targetSet == another.m_targetSet &&
                        m_size == another.m_size &&
                        m_position == another.m_position);

        return !isEqual;
    }

    template <class T>
    BigraphIterator<T>& BigraphIterator<T>::operator++()
    {
        if (m_position != m_size) {
            m_position++;
        }

        return *this;
    }

    template <class T>
    BigraphIterator<T>& BigraphIterator<T>::operator++(int)
    {
        if (m_position != m_size) {
            m_position++;
        }

        return *this;
    }

    template <class T>
    BigraphIterator<T>& BigraphIterator<T>::operator--()
    {
        if (m_position != -1) {
            m_position--;
        }

        return *this;
    }

    template <class T>
    const T* BigraphIterator<T>::operator->() const
    {
        if (m_position < 0 || m_position >= m_size) {
            return &m_emptyValue;
        } else {
            return m_targetSet[m_position];
        }
    }

    template <class T>
    const T& BigraphIterator<T>::operator*() const
    {
        if (m_position < 0 || m_position >= m_size) {
            return m_emptyValue;
        } else {
            return *m_targetSet[m_position];
        }
    }

    template <class T>
    BigraphIterator<T>::~BigraphIterator()
    {
    }
}

#endif // BIGRAPHITERATOR_H_INCLUDED
