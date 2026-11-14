// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77C40 names
// descriptor 0x83817598 AIE_LOW_AMMO under AIEvent. The construction sequence
// ending at 0x82225D90 allocates 0x44 bytes, calls cAIEvent(type 0x23, source),
// and installs table 0x8211F2E8 without adding a payload. Slot 1 is 0x82607C20.
#ifndef AI_CLOWAMMOEVENT_H
#define AI_CLOWAMMOEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cLowAmmoEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cLowAmmoEvent, CD2_SIZE(cLowAmmoEvent, 0x44))
    };
}
// Its initializer has no scaffolded source ownership yet.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cLowAmmoEvent> g_cLowAmmoEvent;
#endif
