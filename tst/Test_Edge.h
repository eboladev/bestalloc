#ifndef TEST_EDGE_H
#define TEST_EDGE_H

#include <QObject>
#include <QTest>

namespace test
{
    class Test_Edge : public QObject
    {
        Q_OBJECT
    public:
        explicit Test_Edge();

    private slots:
        void setUVertex();
        void getUVertex();
        void setVVertex();
        void getVVertex();
        void setWeight();
        void getWeight();

    };
}

#endif // TEST_EDGE_H
