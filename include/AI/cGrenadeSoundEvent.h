// STAND-IN: reference class/base/member names. CD2 constructor 0x8261E030 constructs cSoundEvent
// with event type 0x1A, installs table 0x82123EAC and builds the activator safe pointer at +0x48.
// The constructor converts the activator to its +0x1C safe-deletable base; slot 9 (0x82440548)
// converts it back. Initializer 0x82F7A700 registers AIE_GRENADE_SOUND at 0x83818B10.
#ifndef AI_CGRENADESOUNDEVENT_H
#define AI_CGRENADESOUNDEVENT_H
#include "AI/cSoundEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cGrenadeSoundEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual cCharacterEntityIF *RetInstigator();
        // CD2 0x8261E0F0 overrides cAIEvent slot 8 with 800; its purpose remains unknown.
        virtual int vf8();
        virtual bool Concerns(cNonGameBase *);
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pActivator;
        CD2_LAYOUT_CHECKS(cGrenadeSoundEvent,
            CD2_SIZE(cGrenadeSoundEvent, 0x58)
            CD2_OFFSET(cGrenadeSoundEvent, m_pActivator, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cGrenadeSoundEvent> g_cGrenadeSoundEvent;
#endif
