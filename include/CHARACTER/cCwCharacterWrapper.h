#include "gom/object_prototype.h"
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
        // CD2 spawning initializer 0x82FACF38 names placement factory 0x82540b30.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82540C00: the placement factory (0x82540B30) calls it out of line with the prototype.
        cCwCharacterWrapper(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCwCharacterWrapperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // CHARACTER_CCWCHARACTERWRAPPER_H
