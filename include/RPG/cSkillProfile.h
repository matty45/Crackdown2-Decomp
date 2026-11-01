// RPG::cSkillProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x827534F8) is slot 11 of the vtable at 0x82145B70, as cNonGameBase's RetClassName.
#ifndef RPG_CSKILLPROFILE_H
#define RPG_CSKILLPROFILE_H

#include "gom/non_game_base.h"

namespace RPG
{
    class cSkillProfile : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSkillProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // RPG_CSKILLPROFILE_H
