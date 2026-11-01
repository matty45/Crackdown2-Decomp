// Equip::cUVTurret (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8263BC20) builds cClass(0x1326A, "cUVTurret", 0xAB0); 0xAB0 is the size its registrar gives.
#ifndef EQUIP_CUVTURRET_H
#define EQUIP_CUVTURRET_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cUVTurret
    {
    public:
        static const Fun_Runtime::cClass *ms_pcUVTurretClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CUVTURRET_H
