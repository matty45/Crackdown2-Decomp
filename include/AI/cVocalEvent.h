// STAND-IN: reference name/base. CD2 0x8234B8C0 constructs cSoundEvent, then installs table 0x820FB15C.
// Slot 1 is 0x823E7B20; initializer 0x82F7A808 registers AIE_VOCAL under AIE_SOUND at 0x83818B7C.
#ifndef AI_CVOCALEVENT_H
#define AI_CVOCALEVENT_H
#include "AI/cSoundEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cVocalEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cVocalEvent, CD2_SIZE(cVocalEvent, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cVocalEvent> g_cVocalEvent;
#endif
