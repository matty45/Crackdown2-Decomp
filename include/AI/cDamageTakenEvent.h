// AI::cDamageTakenEvent (Crackdown 2): STAND-IN for the instigator only. Names and types from RuffKing (Burn types the
// instigator as CHARACTER::cCharacter). Evidence:
//   - CD2's registration function 0x82441688 registers "RetInstigator", "RetAmount", "RetHitDirection", "RetHitLocation",
//     "RetDamageType", "RetDamageImpactType" and "RetDamageLocationEnum": the accessors of the reference builds'
//     cDamageTakenEvent, whose first field is m_pInstigator, a safe pointer.
//   - Its "RetInstigator" is 0x823E7C18, which returns the object pointer at 0x50 converted to the object (null stays
//     null, else minus 0x1C, where cNonGameBase holds its cSafeDeletable): the safe pointer is at 0x44.
//   - The linker folded 16 identical getters into 0x823E7C18 ("RetKiller", "RetObject", "RetCarrier", "RetAttacker" and
//     more, each of an event whose first field is a safe pointer) and kept the copy from cAiPlayer's object, so
//     src/AI/cAiPlayer.cpp defines it; this one is named for the class the reference builds and the registration agree on.
#ifndef AI_CDAMAGETAKENEVENT_H
#define AI_CDAMAGETAKENEVENT_H

#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/script_type_registrar.h"
#include "cd2/layout.h"

namespace AI
{
    class cDamageTakenEvent : public cAIEvent
    {
    public:
        // CD2 primary table 0x820FBFF8 slot 1, installed by constructor 0x823EC628.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        cCharacterEntityIF *RetInstigator();
        float RetAmount();
        Fun_Runtime::Vec3 RetHitDirection();
        Fun_Runtime::Vec3 RetHitLocation();
        unsigned int RetDamageImpactType();

    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pInstigator; // 0x44
        // CD2 constructor 0x823EC628 establishes this payload prefix. The enum words precede
        // the amount and vectors in CD2; RuffKing places them after the vectors instead.
        // Enum storage is represented by its observed word/byte types until the enums are recovered.
        unsigned int m_eDamageType;             // 0x54
        unsigned int m_eDamageSubType;          // 0x58
        unsigned char m_eDamageImpactType;      // 0x5C
        char m_nSubTarget;                      // 0x5D
        bool m_bLockedHit;                      // 0x5E
        int m_eDamageLocationEnum;              // 0x60
        float m_fAmount;                       // 0x64
        // CD2 0x823EC628 stores three components and w=1 at +0x70/+0x80; the aligned
        // reference Vec3 members naturally follow the scalar prefix without a padding member.
        Fun_Runtime::Vec3 m_vecHitLocation;      // 0x70
        Fun_Runtime::Vec3 m_vecHitDirection;     // 0x80
        // Descriptive name is ours: constructor records RWS game time here, after both vectors.
        unsigned int m_nRecordedGameTime;       // 0x90


    public:
        CD2_LAYOUT_CHECKS(cDamageTakenEvent,
            CD2_OFFSET(cDamageTakenEvent, m_pInstigator, 0x44)
            CD2_OFFSET(cDamageTakenEvent, m_eDamageType, 0x54)
            CD2_OFFSET(cDamageTakenEvent, m_eDamageSubType, 0x58)
            CD2_OFFSET(cDamageTakenEvent, m_eDamageImpactType, 0x5C)
            CD2_OFFSET(cDamageTakenEvent, m_nSubTarget, 0x5D)
            CD2_OFFSET(cDamageTakenEvent, m_bLockedHit, 0x5E)
            CD2_OFFSET(cDamageTakenEvent, m_eDamageLocationEnum, 0x60)
            CD2_OFFSET(cDamageTakenEvent, m_fAmount, 0x64)
            CD2_OFFSET(cDamageTakenEvent, m_vecHitLocation, 0x70)
            CD2_OFFSET(cDamageTakenEvent, m_vecHitDirection, 0x80)
            CD2_OFFSET(cDamageTakenEvent, m_nRecordedGameTime, 0x90))
    };
}

// CD2 0x82F7AF68 registers AIE_DAMAGE_TAKEN under AIEvent at 0x83818CE0; global name is ours.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cDamageTakenEvent> g_cDamageTakenEvent;

#endif // AI_CDAMAGETAKENEVENT_H
