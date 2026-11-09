// STAND-IN: descriptive class/global names follow CD2's AIE_TIME_PERIOD_CHANGED registration (0x83001C28).
// Construction at 0x82774624 calls cAIEvent for a 0x44-byte object and installs table 0x82147A38,
// whose slot 1 is 0x82773C30. It adds no fields or virtual slots.
#ifndef AI_CTIMEPERIODCHANGEDEVENT_H
#define AI_CTIMEPERIODCHANGEDEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTimePeriodChangedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cTimePeriodChangedEvent, CD2_SIZE(cTimePeriodChangedEvent, 0x44))
    };
}
// Registrar at 0x838517A0; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTimePeriodChangedEvent> g_cTimePeriodChangedEvent;
#endif
