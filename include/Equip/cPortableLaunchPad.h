// CD2 constructor 0x8260DF18 confirms the shared base constructor chain.
#include "Equip/cCWSatchelCharge.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cPortableLaunchPad (Crackdown 2): STAND-IN: constructor-confirmed base and fields. The constructor (0x8260DF18)
// initializes RuffKing's three fields in its order, 0xA0 below RuffKing's offsets; the launch pad ends the class at 0xCA0.
// StaticCreateClass (0x8260DE78) builds cClass(0x27412, "cPortableLaunchPad", 0xCA0); 0xCA0 is the size its registrar gives.
#ifndef EQUIP_CPORTABLELAUNCHPAD_H
#define EQUIP_CPORTABLELAUNCHPAD_H

#include "fun_runtime/class.h"
#include "fun_runtime/safedeletablepointer.h"
#include "PHYSICS/cLaunchPad.h"

namespace Equip
{
    class cPortableLaunchPad : public Equip::cCWSatchelCharge
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260DE68).
        // CD2's MakeNew (0x8260DDD0) allocates 0x430 and inlines the constructor: no fields of its own.
        class cJumpPadPrototype : public cCWSatchelCharge::cCWSatchelChargePrototype
        {
        public:
            __forceinline cJumpPadPrototype(const RWS::CAttributePacket &packet)
                : cCWSatchelCharge::cCWSatchelChargePrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            // CD2: cJumpPadPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8260EC10
        public:
            CD2_LAYOUT_CHECKS(cJumpPadPrototype,
                CD2_SIZE(cJumpPadPrototype, 0x430))
        };

        // CD2 factory 0x8260DE50 forwards only this, without a prototype argument.
        cPortableLaunchPad();
        virtual void Launched(cGameBase *pAttacker); // CD2 primary slot 406: 0x8260E788.
        // CD2 0x8260DE40: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8260DD60 / 0x8260DD70: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 spawning initializer 0x82FCCEA0 names placement factory 0x8260de50.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPortableLaunchPadClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        // The other slots where CD2's table (0x82120F88, stored by the constructor) differs from cCWSatchelCharge's;
        // RuffKing's cPortableLaunchPad overrides the same ones (Unstick aside).
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8260E088
        virtual void TickUpdate(float fDeltaTime); // 23: 0x8260E1F0
        virtual void NotifyTracked(cEquipment *pLastTracked); // 342: 0x8260E4D8
        virtual void NowStuck(); // 432: 0x8260E638
        virtual void Unstick(); // 433: 0x8260E700
        virtual void OnAttachedToObject(cSatchelChargeTarget *pTarget, const Fun_Runtime::Mtx &matOffset); // 434: 0x8260E7B0
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8260E8D8
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x8260E918

    private:
        Fun_Runtime::cSafeDeletablePointer<cPortableLaunchPad> m_pTarget;     // 0xAE0
        unsigned int m_nReplicatedTargetID;                                 // 0xAF0
        PHYSICS::cLaunchPad m_LaunchPad;                                    // 0xB00

        CD2_LAYOUT_CHECKS(cPortableLaunchPad,
            CD2_SIZE(cPortableLaunchPad, 0xCA0)
            CD2_OFFSET(cPortableLaunchPad, m_pTarget, 0xAE0)
            CD2_OFFSET(cPortableLaunchPad, m_nReplicatedTargetID, 0xAF0)
            CD2_OFFSET(cPortableLaunchPad, m_LaunchPad, 0xB00))
    };
}

#endif // EQUIP_CPORTABLELAUNCHPAD_H
