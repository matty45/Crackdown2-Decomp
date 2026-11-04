#ifndef unknown_cAgencyGarageDoor_H
#define unknown_cAgencyGarageDoor_H

#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGarageDoor : public RWS::CAttributeHandler
    {
    public:
        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cAgencyGarageDoor(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcAgencyGarageDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
