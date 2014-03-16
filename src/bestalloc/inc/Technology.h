#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <string>
using namespace std;

namespace bestalloc
{
    class Technology
    {
    private:
        int    m_id;
        string m_name;

    public:
        Technology();
        Technology(int id, const string& name);

        int    getId() const;
        void   setId(int value);
        string getName() const;
        void   setName(string& value);

        ~Technology();
    };
}

#endif // TECHNOLOGY_H
