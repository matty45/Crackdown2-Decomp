// STAND-IN: descriptive class/global names follow CD2's AIE_END_FIRE registration (0x82F7B280).
// Construction at 0x823EF8F4 calls cAIEvent for a 0x44-byte object and installs table 0x820FC090,
// whose slot 1 is 0x823EC870. It adds no fields or virtual slots.
#ifndef AI_CENDFIREEVENT_H
#define AI_CENDFIREEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cEndFireEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cEndFireEvent, CD2_SIZE(cEndFireEvent, 0x44))
    };
}
// Registrar at 0x83818E24; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cEndFireEvent> g_cEndFireEvent;
#endif
