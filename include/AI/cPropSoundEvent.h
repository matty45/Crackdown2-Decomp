// STAND-IN: reference class/base/member names. CD2 construction in cProp at 0x8272AEAC calls
// cSoundEvent with type 0x1B, installs table 0x8213D8A0 and builds the activator pointer at +0x48.
// The activator is converted to its +0x1C safe-deletable base, as in cGrenadeSoundEvent.
// Initializer 0x82F7A758 registers AIE_PROP_SOUND under AIE_SOUND at 0x83818B34.
#ifndef AI_CPROPSOUNDEVENT_H
#define AI_CPROPSOUNDEVENT_H
#include "AI/cSoundEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cPropSoundEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual cCharacterEntityIF *RetInstigator();
        virtual bool Concerns(cNonGameBase *);
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pActivator;
        CD2_LAYOUT_CHECKS(cPropSoundEvent,
            CD2_SIZE(cPropSoundEvent, 0x58)
            CD2_OFFSET(cPropSoundEvent, m_pActivator, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cPropSoundEvent> g_cPropSoundEvent;
#endif
