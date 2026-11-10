#include "gom/object_prototype.h"
// CHARACTER::cCharacter (Crackdown 2): STAND-IN, sized to CD2. Only what matched code needs so far. Evidence:
//   - Size 0x2CC0: its StaticCreateClass builds cClass(0, "cCharacter", 0x2CC0); its constructor is 0x82543408.
//   - Bases: CD2 constructor 0x82543408 calls cCharacterMotion's (0x82308218) and constructs
//     cSatchelChargeTarget at +0x11F0 (table 0x82124730), agreeing with RuffKing's base order.
//     The inherited cIgnitable owns the fire flag at +0x261; cReplicatedClass owns m_nObjectID at +0x548.
//   - m_pTargeting (0x1524): cCwCharacterWrapper's constructor stores its TGT::cAiTargeting (0x2F40) there and its
//     PoiIF (0x2FA0) at 0x1528, RuffKing's m_pTargeting / m_pPoiIF pair (at 0x1534 / 0x1538 in RuffKing).
//   - m_eLODLevel (0x2812; RuffKing's unsigned char m_eLODLevel at 0x2822): cCharacterInterface's script method
//     "RetLODLevel" (0x8254E8C8) returns the character's byte at 0x2812, and cAiPlayer::ShouldTriggerFootStepEvent
//     (0x823EB518) compares it with 1, as RuffKing's does through RetLODLevel.
// Primary table 0x821130C8 has 452 slots; cCharacter adds 347..451 after cCharacterMotion's 347 slots.
// The script wrapper at 0x823EC048 calls slot 371, RetCharacterState in RuffKing.
#ifndef CHARACTER_CCHARACTER_H
#define CHARACTER_CCHARACTER_H

#include "CHARACTER/cCharacterMotion.h"
#include "Equip/cSatchelChargeTarget.h"
#include "CHARACTER/ePowerUp.h"
#include "TGT/cTargeting.h"
#include "CHARACTER/cActionManager.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cCharacter : public cCharacterMotion, public Equip::cSatchelChargeTarget
    {
    public:
        // CD2 spawning initializer 0x82FAD7A8 names placement factory 0x822643a0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcCharacterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled11F8[0x1524 - 0x11F8];
    protected:
        TGT::cTargeting *m_pTargeting;          // 0x1524
    private:
        unsigned char m_unmodelled1528[0x1530 - 0x1528];
        cActionManager m_ActionManager;
        unsigned char m_unmodelled1B30[0x2812 - 0x1B30];
    protected:
        unsigned char m_eLODLevel;              // 0x2812
    private:
        unsigned char m_pad2813[0x2815 - 0x2813];
        // CD2 script getters 0x825430B0/0x825430C0 read bits 5/4. Byte name is ours.
        unsigned char m_flags2815;
        unsigned char m_pad2816[0x2CC0 - 0x2816];

    public:
        // STAND-IN: RuffKing names this nested prototype; CD2 MakeNew (0x82542FE0) allocates 0x330 bytes
        // and calls its out-of-line packet constructor at 0x8254D4C8. Additional fields remain unmodelled.
        class cCharacterPrototype : public cCharacterMotion::cCharacterMotionPrototype
        {
        private:
            unsigned char m_unmodelled280[0x330 - 0x280];
        public:
            cCharacterPrototype(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cCharacterPrototype,
                CD2_SIZE(cCharacterPrototype, 0x330))
        };

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 cReplicatedClass slot 23 (0x825430D0).
        virtual unsigned int GetMaxReplicatedFields() const;
        bool IsInGodMode() const;
        bool IsInfiniteAmmo() const;
        // CD2 0x82543058; RuffKing/Burn name it.
        bool IsUsingInfiniteAmmo();
        bool RetIsOnFire() const { return IsOnFire(); }
        unsigned char RetLODLevel() const { return m_eLODLevel; }
        TGT::cTargeting *RetTargeting() { return m_pTargeting; }
        cActionManager &RetActionManager() { return m_ActionManager; }
        const cActionManager &RetActionManager() const { return m_ActionManager; }
        Equip::cEquipment *RetEquipmentOfType(unsigned int type)
        {
            return m_ActionManager.RetCharacterStateInfo().RetInventory().RetItemWithEquipmentID(type);
        }
        Equip::cEquipment *RetRealCurrentPrimaryEquipment()
        {
            return m_ActionManager.RetCharacterStateInfo().RetInventory().RetPrimary();
        }

        // The six pure slots of cCharacterMotion are implemented by CD2's cCharacter table.
        virtual void vf341(); virtual void vf342(); virtual void vf343();
        virtual void vf344(); virtual void vf345(); virtual void vf346();
        // Remaining own virtual names are unrecovered; slot-number placeholders preserve the evidenced order.
        virtual void vf347();
        virtual void vf348();
        virtual void vf349();
        virtual void vf350();
        virtual void vf351();
        virtual void vf352();
        virtual void vf353();
        virtual void vf354();
        virtual void vf355();
        virtual void vf356();
        virtual void vf357();
        virtual void vf358();
        virtual void vf359();
        virtual void vf360();
        virtual void vf361();
        virtual void vf362();
        virtual void vf363();
        virtual void vf364();
        virtual void vf365();
        virtual void vf366();
        virtual void vf367();
        virtual void vf368();
        virtual void vf369();
        virtual void vf370();
        virtual unsigned int RetCharacterState(); // CD2 primary slot 371
        virtual void vf372();
        virtual void vf373();
        virtual void vf374();
        virtual void vf375();
        virtual void vf376();
        virtual void vf377();
        virtual void vf378();
        virtual void vf379();
        virtual void vf380();
        virtual char RetSkill(unsigned int skill) const;
        virtual bool IsSkillAndBonusMaxed(unsigned int skill) const;
        virtual bool IsSkillMaxed(unsigned int skill) const;
        virtual void vf384();
        virtual void vf385();
        virtual void vf386();
        virtual void vf387();
        virtual void vf388();
        virtual void vf389();
        virtual void vf390();
        virtual bool IsTransformationRequired() const;
        virtual void vf392();
        virtual unsigned char RetAthleticLevel() const;
        virtual unsigned char RetExplosivesLevel() const;
        virtual unsigned char RetStrengthLevel() const;
        virtual void vf396();
        virtual unsigned char RetFirearmsLevel() const;
        virtual void vf398();
        virtual void vf399();
        virtual void vf400();
        virtual void vf401();
        virtual void vf402();
        virtual void vf403();
        virtual bool IsInDeathLimbo() const;
        virtual void vf405();
        virtual void vf406();
        virtual void vf407();
        virtual void vf408();
        virtual void SetKilledByFriendly(bool);
        virtual void vf410();
        virtual void vf411();
        virtual void vf412();
        virtual void vf413();
        virtual bool IsPowerUpActive(ePowerUp);
        virtual void vf415();
        virtual void vf416();
        virtual void vf417();
        virtual void vf418();
        virtual void vf419();
        virtual void vf420();
        virtual void vf421();
        virtual void vf422();
        virtual void vf423();
        virtual void vf424();
        virtual void vf425();
        virtual void vf426();
        virtual void vf427();
        virtual void vf428();
        virtual void vf429();
        virtual void vf430();
        virtual void vf431();
        virtual void vf432();
        virtual void vf433();
        virtual void vf434();
        virtual void vf435();
        virtual void vf436();
        virtual void vf437();
        virtual void vf438();
        virtual void vf439();
        virtual void vf440();
        // Slots 441/442: Burn's RetReplicatedBehaviourState/ForceReplicatedBehaviourState (consecutive there);
        // cCwCharacter's overrides (0x8253F4C8/0x8253F4D0) read and write its byte at 0x2CC8.
        virtual unsigned char RetReplicatedBehaviourState() const;
        virtual void ForceReplicatedBehaviourState(unsigned char nState);
        virtual void vf443();
        virtual void vf444();
        virtual unsigned int RetLastVehicleHitID() const;
        virtual void vf446();
        virtual void vf447();
        virtual void vf448();
        virtual void vf449();
        virtual void vf450();
        virtual void vf451();

        CD2_LAYOUT_CHECKS(cCharacter,
            CD2_SIZE(cCharacter, 0x2CC0)
            CD2_OFFSET(cCharacter, m_nObjectID, 0x548)
            CD2_OFFSET(cCharacter, m_pTargeting, 0x1524)
            CD2_OFFSET(cCharacter, m_ActionManager, 0x1530)
            CD2_OFFSET(cCharacter, m_eLODLevel, 0x2812)
            CD2_OFFSET(cCharacter, m_flags2815, 0x2815))
    };
}

#endif // CHARACTER_CCHARACTER_H
