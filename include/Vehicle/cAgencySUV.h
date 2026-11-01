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
        static const Fun_Runtime::cClass *ms_pcAgencySUVClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYSUV_H
