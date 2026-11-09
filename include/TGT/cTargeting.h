// TGT::cTargeting (Crackdown 2): STAND-IN. The base of the targeting classes a character points at through
// CHARACTER::cCharacter::m_pTargeting. Layout from RuffKing (8 bytes: the vptr, then m_pOwner); its vtable (over 40
// slots in RuffKing) is modelled through CD2 slot 23 only. The script-named cCharacterInterface::RetVehicleTarget
// (0x8254E958) calls that slot; the preceding names/signatures remain unrecovered.
#ifndef TGT_CTARGETING_H
#define TGT_CTARGETING_H

#include "cd2/layout.h"

namespace CHARACTER { class cCharacter; }
class cGameBase;

namespace TGT
{
    class cTargeting
    {
    public:
        virtual void Slot0();
        virtual void Slot1();
        virtual void Slot2();
        virtual void Slot3();
        virtual void Slot4();
        virtual void Slot5();
        virtual void Slot6();
        virtual void Slot7();
        virtual void Slot8();
        virtual void Slot9();
        virtual void Slot10();
        virtual void Slot11();
        virtual void Slot12();
        virtual void Slot13();
        virtual void Slot14();
        virtual void Slot15();
        virtual void Slot16();
        virtual void Slot17();
        virtual void Slot18();
        virtual void Slot19();
        virtual void Slot20();
        virtual void Slot21();
        virtual void Slot22();
        virtual cGameBase *RetVehicleTarget();
    protected:
        CHARACTER::cCharacter *m_pOwner;

    public:
        CD2_LAYOUT_CHECKS(cTargeting,
            CD2_SIZE(cTargeting, 0x8)
            CD2_OFFSET(cTargeting, m_pOwner, 0x4))
    };
}

#endif // TGT_CTARGETING_H
