/*! ---------------------------------------------------------------
 * \file   Test_Employee.h
 * \brief  Test suite for Employee class
 * \author Konstantin Stepanov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */
#ifndef TEST_EMPLOYEE_H
#define TEST_EMPLOYEE_H

#include <QObject>
#include <QTest>

namespace test
{


    class Test_Employee : public QObject
    {
        Q_OBJECT
    public:
        Test_Employee();
    
    private slots:
        void getId();
        void setId();
        void getName();
        void setName();
    
};

}
#endif // TEST_EMPLOYEE_H
