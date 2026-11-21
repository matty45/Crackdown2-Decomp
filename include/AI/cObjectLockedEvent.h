// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77C98 registers
// AIE_OBJECT_LOCKED under AIEvent at 0x838175BC. Construction at 0x82686C2C
// calls cAIEvent(type 0x64, source) in a 0x44-byte allocation and installs table
// 0x82132468 without adding a payload. Its slot 1 is 0x82684C58.
#ifndef AI_COBJECTLOCKEDEVENT_H
#define AI_COBJECTLOCKEDEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cObjectLockedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cObjectLockedEvent, CD2_SIZE(cObjectLockedEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cObjectLockedEvent> g_cObjectLockedEvent;
#endif
