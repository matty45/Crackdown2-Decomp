#include "rws/attributes.h"
// CHARACTER::cCwCharacterWrapper (Crackdown 2): STAND-IN for the class name only. Base CHARACTER::cCwCharacter, as in
// RuffKing's header; RetClassName (0x82540B20) is slot 11 of the vtable at 0x82017DC8, as cNonGameBase's RetClassName.
#ifndef CHARACTER_CCWCHARACTERWRAPPER_H
#define CHARACTER_CCWCHARACTERWRAPPER_H

#include "CHARACTER/cCwCharacter.h"
#include "fun_runtime/class.h"

namespace CHARACTER
{
    class cCwCharacterWrapper : public CHARACTER::cCwCharacter
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCwCharacterWrapperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // CHARACTER_CCWCHARACTERWRAPPER_H
