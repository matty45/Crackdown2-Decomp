// STAND-IN: descriptive class/global names follow CD2's AIE_TODDUSK registration (0x83001B78).
// Construction at 0x82775470 calls cAIEvent for a 0x44-byte object and installs table 0x821479F0,
// whose slot 1 is 0x82773C10. It adds no fields or virtual slots.
#ifndef AI_CTODDUSKEVENT_H
#define AI_CTODDUSKEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTODDuskEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cTODDuskEvent, CD2_SIZE(cTODDuskEvent, 0x44))
    };
}
// Registrar at 0x83851758; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTODDuskEvent> g_cTODDuskEvent;
#endif
