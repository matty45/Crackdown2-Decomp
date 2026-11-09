// STAND-IN: descriptive class/global names follow CD2's AIE_SHOTS_COUNTER registration (0x82F782B8).
// Construction at 0x82377280 calls cAIEvent's constructor for a 0x44-byte object, then installs
// primary table 0x820FB114, whose slot 1 is 0x823E7AA0. It adds no fields or virtual slots.
#ifndef AI_CSHOTSCOUNTEREVENT_H
#define AI_CSHOTSCOUNTEREVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cShotsCounterEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cShotsCounterEvent, CD2_SIZE(cShotsCounterEvent, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cShotsCounterEvent> g_cShotsCounterEvent;
#endif
