// CHARACTER::cGenCharProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x82556360) is slot 11 of the vtable at 0x82114298, as cNonGameBase's RetClassName.
#ifndef CHARACTER_CGENCHARPROFILE_H
#define CHARACTER_CGENCHARPROFILE_H

#include "gom/non_game_base.h"

namespace CHARACTER
{
    class cGenCharProfile : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcGenCharProfileClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // CHARACTER_CGENCHARPROFILE_H
