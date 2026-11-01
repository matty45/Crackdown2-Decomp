// Vehicle::cAgencyBuggy (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826E9EB8) builds cClass(0x12064, "cAgencyBuggy", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYBUGGY_H
#define VEHICLE_CAGENCYBUGGY_H

#include "fun_runtime/class.h"

namespace Vehicle
{
    class cAgencyBuggy
    {
    public:
        static const Fun_Runtime::cClass *ms_pcAgencyBuggyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // VEHICLE_CAGENCYBUGGY_H
