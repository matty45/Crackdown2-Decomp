#ifndef CHARACTER_cCwGoliathCharacterWrapper_H
#define CHARACTER_cCwGoliathCharacterWrapper_H

#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace CHARACTER
{
    class cCwGoliathCharacterWrapper : public RWS::CAttributeHandler
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cCwGoliathCharacterWrapper(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcCwGoliathCharacterWrapperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
