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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySportsClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYSPORTS_H
