// STAND-IN: reference name/base/member. CD2 constructor 0x823E7B38 calls cSoundEvent's constructor,
// installs primary table 0x820033DC and constructs the attacker safe pointer at +0x48.
// Slot 1 is 0x823E7BE8; initializer 0x82F7A860 registers AIE_PAIN_VOCAL under AIE_SOUND at 0x83818BA0.
#ifndef AI_CPAINVOCALEVENT_H
#define AI_CPAINVOCALEVENT_H
#include "AI/cSoundEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cPainVocalEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool Concerns(cNonGameBase *);
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pAttacker;
        CD2_LAYOUT_CHECKS(cPainVocalEvent,
            CD2_SIZE(cPainVocalEvent, 0x58)
            CD2_OFFSET(cPainVocalEvent, m_pAttacker, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cPainVocalEvent> g_cPainVocalEvent;
#endif
