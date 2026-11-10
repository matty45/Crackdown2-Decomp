// STAND-IN: descriptive class/global names follow CD2's AIE_PLAYER_AI_BREAKOUT_ATTEMPT registration (0x82F77FF8).
// Construction at 0x82330730 calls cAIEvent (0x822137C0) for a 0x44-byte object and installs table 0x8213D558,
// whose slot 1 is 0x8271F168. It adds no fields or virtual slots.
#ifndef AI_CPLAYERAIBREAKOUTATTEMPTEVENT_H
#define AI_CPLAYERAIBREAKOUTATTEMPTEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cPlayerAIBreakoutAttemptEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cPlayerAIBreakoutAttemptEvent, CD2_SIZE(cPlayerAIBreakoutAttemptEvent, 0x44))
    };
}
// Registrar at 0x83817704; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cPlayerAIBreakoutAttemptEvent> g_cPlayerAIBreakoutAttemptEvent;
#endif
