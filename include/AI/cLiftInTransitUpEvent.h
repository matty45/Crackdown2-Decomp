// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77820 registers
// AIE_LIFT_IN_TRANSIT_UP under AIEvent at 0x838173E8. Construction at 0x82739D0C
// calls cAIEvent(type 0x89, source) in a 0x44-byte allocation and installs table
// 0x8213F75C without adding a payload. Its slot 1 is 0x82738F48.
#ifndef AI_CLIFTINTRANSITUPEVENT_H
#define AI_CLIFTINTRANSITUPEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cLiftInTransitUpEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cLiftInTransitUpEvent, CD2_SIZE(cLiftInTransitUpEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cLiftInTransitUpEvent> g_cLiftInTransitUpEvent;
#endif
