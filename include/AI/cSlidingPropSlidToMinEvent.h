// STAND-IN: descriptive C++ name is ours. CD2 0x82FF63C8 registers descriptor
// 0x8384AF64 as AIE_SLIDING_PROP_SLID_TO_MIN under AIEvent. Construction
// at 0x8273CEC0 uses cAIEvent(type 116, source), size 0x44, and primary table
// 0x82140D74; slot 1 is 0x8273B5D0. There is no additional payload.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cSlidingPropSlidToMinEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cSlidingPropSlidToMinEvent, CD2_SIZE(cSlidingPropSlidToMinEvent, 0x44))
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cSlidingPropSlidToMinEvent> g_cSlidingPropSlidToMinEvent;
