#include "gom/object_prototype.h"
#ifndef unknown_cTransVehicleDamageProp_H
#define unknown_cTransVehicleDamageProp_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cTransVehicleDamageProp : public RWS::CAttributeHandler
    {
    public:
        // CD2 spawning initializer 0x82FF5B30 names placement factory 0x82730cb8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcTransVehicleDamagePropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
