#ifndef SKILL_H
#define SKILL_H

#include <string>
using namespace std;

#include "Technology.h"

namespace bestalloc
{
    class Skill
    {
    private:
        Technology m_technology;
        int        m_level;

    public:
        Skill();
        Skill(const Technology& technology, int level);

        Technology getTechnology() const;
        void       setTechnology(const Technology& value);
        int        getLevel() const;
        void       setLevel(int value);

        ~Skill();
    };
}


#endif // SKILL_H
