// STAND-IN: descriptive C++ name is ours. CD2 0x82FF6420 registers descriptor
// 0x8384AF88 as AIE_SLIDING_PROP_SLID_TO_MAX under AIEvent. Construction
// at 0x8273D050 uses cAIEvent(type 117, source), size 0x44, and primary table
// 0x82140D98; slot 1 is 0x8273B5E0. There is no additional payload.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cSlidingPropSlidToMaxEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cSlidingPropSlidToMaxEvent, CD2_SIZE(cSlidingPropSlidToMaxEvent, 0x44))
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cSlidingPropSlidToMaxEvent> g_cSlidingPropSlidToMaxEvent;
