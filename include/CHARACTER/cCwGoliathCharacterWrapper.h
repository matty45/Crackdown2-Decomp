#include "gom/object_prototype.h"
#ifndef CHARACTER_cCwGoliathCharacterWrapper_H
#define CHARACTER_cCwGoliathCharacterWrapper_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "CHARACTER/cCwCharacter.h"

namespace CHARACTER
{
    class cCwGoliathCharacterWrapper : public cCwCharacter
    {
    public:
        // CD2 spawning initializer 0x82FAD370 names placement factory 0x82542228.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82542318: the placement factory (0x82542228) calls it out of line with the prototype.
        cCwGoliathCharacterWrapper(GOM::cObjectPrototype *);
        static const Fun_Runtime::cClass *ms_pcCwGoliathCharacterWrapperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
