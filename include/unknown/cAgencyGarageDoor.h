#include "gom/object_prototype.h"
#ifndef unknown_cAgencyGarageDoor_H
#define unknown_cAgencyGarageDoor_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyGarageDoor : public RWS::CAttributeHandler
    {
    public:
        // CD2 spawning initializer 0x82FF6868 names placement factory 0x82732e48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcAgencyGarageDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
