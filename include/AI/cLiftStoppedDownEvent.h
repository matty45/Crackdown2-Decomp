// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77928 registers
// AIE_LIFT_STOPPED_DOWN under AIEvent at 0x83817454. Construction at 0x8273A024
// calls cAIEvent(type 0x8B, source) in a 0x44-byte allocation and installs table
// 0x8213F7C8 without adding a payload. Its slot 1 is 0x82738F78.
#ifndef AI_CLIFTSTOPPEDDOWNEVENT_H
#define AI_CLIFTSTOPPEDDOWNEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cLiftStoppedDownEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cLiftStoppedDownEvent, CD2_SIZE(cLiftStoppedDownEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cLiftStoppedDownEvent> g_cLiftStoppedDownEvent;
#endif
