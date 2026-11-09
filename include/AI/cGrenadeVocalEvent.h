// STAND-IN: reference name/base/member. CD2 construction at 0x8234BC14 calls cSoundEvent, then builds
// the grenade safe pointer at +0x48 and installs primary table 0x820FB1D0 (slot 1: 0x823E7C08).
// Initializer 0x82F7A910 registers AIE_GRENADE_VOCAL under AIE_SOUND at 0x83818BE8.
#ifndef AI_CGRENADEVOCALEVENT_H
#define AI_CGRENADEVOCALEVENT_H
#include "AI/cSoundEvent.h"
#include "PHYSICS/cDynamicBody.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cGrenadeVocalEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool Concerns(cNonGameBase *);
    protected:
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pGrenade;
        CD2_LAYOUT_CHECKS(cGrenadeVocalEvent,
            CD2_SIZE(cGrenadeVocalEvent, 0x58)
            CD2_OFFSET(cGrenadeVocalEvent, m_pGrenade, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cGrenadeVocalEvent> g_cGrenadeVocalEvent;
#endif
