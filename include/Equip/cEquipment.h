// Equip::cEquipment (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cEquipment
    {
    public:
        static const Fun_Runtime::cClass *ms_pcEquipmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CEQUIPMENT_H
