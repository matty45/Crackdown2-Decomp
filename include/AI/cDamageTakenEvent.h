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

    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pInstigator; // 0x44

    public:
        CD2_LAYOUT_CHECKS(cDamageTakenEvent,
            CD2_OFFSET(cDamageTakenEvent, m_pInstigator, 0x44))
    };
}

// CD2 0x82F7AF68 registers AIE_DAMAGE_TAKEN under AIEvent at 0x83818CE0; global name is ours.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cDamageTakenEvent> g_cDamageTakenEvent;

#endif // AI_CDAMAGETAKENEVENT_H
