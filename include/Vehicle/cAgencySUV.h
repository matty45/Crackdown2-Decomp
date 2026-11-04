#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySUV (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826FBC38) builds cClass(0x12060, "cAgencySUV", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSUV_H
#define VEHICLE_CAGENCYSUV_H

#include "fun_runtime/class.h"

namespace Vehicle
{
    class cAgencySUV
    {
    public:
        // CD2 0x826FBA68: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEC228 names placement factory 0x826fba78.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySUVClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYSUV_H
