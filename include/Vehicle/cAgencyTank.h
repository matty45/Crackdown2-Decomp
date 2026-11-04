#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencyTank (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826FC730) builds cClass(0x120AB, "cAgencyTank", 0x3150); 0x3150 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYTANK_H
#define VEHICLE_CAGENCYTANK_H

#include "fun_runtime/class.h"

namespace Vehicle
{
    class cAgencyTank
    {
    public:
        // CD2 0x826FC708: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEC660 names placement factory 0x826fc718.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyTankClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYTANK_H
