// STAND-IN: descriptive class/global names follow CD2's AIE_TODDAWN registration (0x83001BD0).
// Construction at 0x82775348 calls cAIEvent for a 0x44-byte object and installs table 0x82147A14,
// whose slot 1 is 0x82773C20. It adds no fields or virtual slots.
#ifndef AI_CTODDAWNEVENT_H
#define AI_CTODDAWNEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTODDawnEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cTODDawnEvent, CD2_SIZE(cTODDawnEvent, 0x44))
    };
}
// Registrar at 0x8385177C; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTODDawnEvent> g_cTODDawnEvent;
#endif
