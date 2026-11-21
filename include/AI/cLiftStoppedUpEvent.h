// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F778D0 registers
// AIE_LIFT_STOPPED_UP under AIEvent at 0x83817430. Construction at 0x8273A0D0
// calls cAIEvent(type 0x8C, source) in a 0x44-byte allocation and installs table
// 0x8213F7A4 without adding a payload. Its slot 1 is 0x82738F68.
#ifndef AI_CLIFTSTOPPEDUPEVENT_H
#define AI_CLIFTSTOPPEDUPEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cLiftStoppedUpEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cLiftStoppedUpEvent, CD2_SIZE(cLiftStoppedUpEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cLiftStoppedUpEvent> g_cLiftStoppedUpEvent;
#endif
