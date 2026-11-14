// STAND-IN: interface only, not an allocation layout. The C++ class name is
// descriptive and ours: CD2 registers the script type AIE_GRENADE_APPEARED under
// AIEvent at 0x82F7CA80, using descriptor 0x8381993C. Satchel observer code
// 0x8261B180 constructs its cAIEvent base and installs table 0x82123CE8;
// slot 1 is the metadata getter at 0x8261A238. The grenade payload is not exposed here.
#ifndef AI_CGRENADEAPPEAREDEVENT_H
#define AI_CGRENADEAPPEAREDEVENT_H
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cGrenadeAppearedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    };
}
// The descriptor's initializer is outside the scaffolded splits, so it remains external.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cGrenadeAppearedEvent> g_cGrenadeAppearedEvent;
#endif
