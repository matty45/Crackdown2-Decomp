// STAND-IN: descriptive class/global names follow CD2's AIE_REINCARNATED registration (0x82F7B0C8).
// Construction at 0x82721110 calls cAIEvent (0x822137C0) for a 0x44-byte object and installs table 0x8213D5A0,
// whose slot 1 is 0x8271F188. It adds no fields or virtual slots.
#ifndef AI_CREINCARNATEDEVENT_H
#define AI_CREINCARNATEDEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cReincarnatedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cReincarnatedEvent, CD2_SIZE(cReincarnatedEvent, 0x44))
    };
}
// Registrar at 0x83818D70; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cReincarnatedEvent> g_cReincarnatedEvent;
#endif
