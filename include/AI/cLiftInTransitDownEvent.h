// STAND-IN: descriptive C++ name is ours. CD2 initializer 0x82F77878 registers
// AIE_LIFT_IN_TRANSIT_DOWN under AIEvent at 0x8381740C. Construction at 0x82739DCC
// calls cAIEvent(type 0x8A, source) in a 0x44-byte allocation and installs table
// 0x8213F780 without adding a payload. Its slot 1 is 0x82738F58.
#ifndef AI_CLIFTINTRANSITDOWNEVENT_H
#define AI_CLIFTINTRANSITDOWNEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cLiftInTransitDownEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cLiftInTransitDownEvent, CD2_SIZE(cLiftInTransitDownEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cLiftInTransitDownEvent> g_cLiftInTransitDownEvent;
#endif
