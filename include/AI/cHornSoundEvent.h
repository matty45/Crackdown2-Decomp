// STAND-IN: reference name/base. CD2 construction at 0x822D2974 calls cSoundEvent
// with type 0x1C in a 0x48-byte allocation, then installs table 0x82135588 with
// no extra payload. Initializer 0x82F7A7B0 registers AIE_HORN_SOUND under
// AIE_SOUND at 0x83818B58. The event's slot-1 getter is 0x826CC850.
#ifndef AI_CHORNSOUNDEVENT_H
#define AI_CHORNSOUNDEVENT_H
#include "AI/cSoundEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cHornSoundEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cHornSoundEvent, CD2_SIZE(cHornSoundEvent, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cHornSoundEvent> g_cHornSoundEvent;
#endif
