// Method-only STAND-IN: descriptive C++ name is ours. CD2 initializer
// 0x82F78520 names descriptor 0x83817920 AIE_GANG_ENFORCER_LEVEL_CHANGED
// under AIEvent. Construction in 0x82676860 allocates 0x50 bytes, calls
// cAIEvent(type 133, source), and installs table 0x8212E96C. Its three payload
// words at +0x44/+0x48/+0x4C remain unmodelled. Slot 1 is 0x82676318.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cGangEnforcerLevelChangedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cGangEnforcerLevelChangedEvent> g_cGangEnforcerLevelChangedEvent;
