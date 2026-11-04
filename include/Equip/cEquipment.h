#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cEquipment (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/cStateMachine.h"

namespace Equip
{
    class cEquipment : public PHYSICS::cNetDynamicBody, public Fun_Runtime::cStateMachine
    {
    public:
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cEquipmentPrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype {};

        // CD2 placement factory forwards only this; later reference builds add a prototype argument.
        cEquipment();
        // CD2 0x826046A8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCB2A0 names placement factory 0x826046b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcEquipmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor 0x82604AF8: reference hierarchy, descriptor size 0x870.
        unsigned char m_unmodelled7A4[0x870 - 0x7A4];
        CD2_LAYOUT_CHECKS(cEquipment, CD2_SIZE(cEquipment, 0x870))
    };
}

#endif // EQUIP_CEQUIPMENT_H
