// STAND-IN: descriptive class/global names follow CD2's AIE_CARRIED_OBJECT_LOST registration (0x82F7B178).
// Construction at 0x823EFFE4 calls cAIEvent for a 0x44-byte object and installs table 0x820FC048,
// whose slot 1 is 0x823EC850. It adds no fields or virtual slots.
#ifndef AI_CCARRIEDOBJECTLOSTEVENT_H
#define AI_CCARRIEDOBJECTLOSTEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cCarriedObjectLostEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cCarriedObjectLostEvent, CD2_SIZE(cCarriedObjectLostEvent, 0x44))
    };
}
// Registrar at 0x83818DB8; CD2 registers this type under AIEvent.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cCarriedObjectLostEvent> g_cCarriedObjectLostEvent;
#endif
