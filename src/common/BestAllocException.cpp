#include "BestAllocException.h"
using namespace bestalloc;

BestAllocException::BestAllocException(int errorCode, const QString& description)
    : m_errorCode(errorCode),
      m_description(description)
{
}

void BestAllocException::setErrorCode(int value)
{
    m_errorCode = value;
}

int BestAllocException::getErrorCode() const
{
    return m_errorCode;
}

void BestAllocException::setDescription(const QString& value)
{
    m_description = value;
}

QString BestAllocException::getDescription() const
{
    return m_description;
}

BestAllocException::~BestAllocException()
{
}
