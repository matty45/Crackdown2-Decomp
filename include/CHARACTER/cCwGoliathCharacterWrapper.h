#include "gom/object_prototype.h"
#ifndef CHARACTER_cCwGoliathCharacterWrapper_H
#define CHARACTER_cCwGoliathCharacterWrapper_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace CHARACTER
{
    class cCwGoliathCharacterWrapper : public RWS::CAttributeHandler
    {
    public:
        // CD2 spawning initializer 0x82FAD370 names placement factory 0x82542228.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcCwGoliathCharacterWrapperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
