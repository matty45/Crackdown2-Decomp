// STAND-IN: descriptive class/global names follow CD2's AIE_DEADPLAYER registration (0x82F7B018).
// Construction at 0x827201EC calls cAIEvent (0x822137C0) for a 0x44-byte object and installs table 0x8213D57C,
// whose slot 1 is 0x8271F178. It adds no fields or virtual slots.
#ifndef AI_CDEADPLAYEREVENT_H
#define AI_CDEADPLAYEREVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cDeadPlayerEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cDeadPlayerEvent, CD2_SIZE(cDeadPlayerEvent, 0x44))
    };
}
// Registrar at 0x83818D28; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cDeadPlayerEvent> g_cDeadPlayerEvent;
#endif
