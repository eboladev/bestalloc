/*! ---------------------------------------------------------------
 * \file   BestAllocException.h
 * \brief  BestAllocException class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef BESTALLOCEXCEPTION_H_INCLUDED
#define BESTALLOCEXCEPTION_H_INCLUDED

#include <QString>

namespace bestalloc
{
    class BestAllocException
    {
    private:
        int     m_errorCode;
        QString m_description;

    public:
        BestAllocException(int errorCode, const QString& description);

        void setErrorCode(int value);
        int  getErrorCode() const;

        void setDescription(const QString& value);
        QString getDescription() const;

        ~BestAllocException();
    };
}

#endif // BESTALLOCEXCEPTION_H_INCLUDED
