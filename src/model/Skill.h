/*! ---------------------------------------------------------------
 * \file   Skill.h
 * \brief  Skill class declaration
 * \author Edward Ryabikov
 *
 * PROJ: bestalloc
 * ---------------------------------------------------------------- */

#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include <string>
#include <QDataStream>
using namespace std;

namespace bestalloc
{
    class Skill
    {
    private:
        int    m_id;
        string m_name;

    public:
        Skill();
        Skill(int id, const string& name);

        int    getId() const;
        void   setId(int value);
        string getName() const;
        void   setName(string& value);

        ~Skill();
    };
}


#endif // SKILL_H_INCLUDED
