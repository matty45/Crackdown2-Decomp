#include "gom/object_prototype.h"
// Base cVehicleDamageProp: CD2's inheritance registrar names it, and the destructor 0x82730E98 calls cVehicleDamageProp's
// (0x8234EC90). Derived storage is not modelled.
#ifndef unknown_cTransVehicleDamageProp_H
#define unknown_cTransVehicleDamageProp_H

#include "Prop/cVehicleDamageProp.h"

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cTransVehicleDamageProp : public Prop::cVehicleDamageProp
    {
    public:
        // CD2 0x82730D78, called by the placement factory 0x82730CB8.
        cTransVehicleDamageProp(GOM::cObjectPrototype *);
        // CD2 0x82730E98.
        virtual ~cTransVehicleDamageProp();
        // CD2 spawning initializer 0x82FF5B30 names placement factory 0x82730cb8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcTransVehicleDamagePropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
