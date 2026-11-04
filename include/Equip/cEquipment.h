#include "rws/attributes.h"
// Equip::cEquipment (Crackdown 2): STAND-IN. Base PHYSICS::cNetDynamicBody (its inheritance registrar); fields not modelled.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace Equip
{
    class cEquipment : public PHYSICS::cNetDynamicBody
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcEquipmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // Out of line: CD2 0x82604AF8 (SpawnFromPrototype tail-calls it).
        cEquipment();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);

    private:
        unsigned char m_unmodelled7A0[0x870 - 0x7A0];

        CD2_LAYOUT_CHECKS(cEquipment, CD2_SIZE(cEquipment, 0x870))
    };
}

#endif // EQUIP_CEQUIPMENT_H
