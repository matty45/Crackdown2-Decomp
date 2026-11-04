#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySports (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826ED348) builds cClass(0x12061, "cAgencySports", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSPORTS_H
#define VEHICLE_CAGENCYSPORTS_H

#include "fun_runtime/class.h"

namespace Vehicle
{
    class cAgencySports
    {
    public:
        // CD2 0x826ECEC8: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826ECF90: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEB980 names placement factory 0x826ecfa0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySportsClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYSPORTS_H
