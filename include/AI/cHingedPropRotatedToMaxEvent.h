// STAND-IN: descriptive C++ name is ours. CD2 0x82FF6370 registers descriptor
// 0x8384AF40 as AIE_HINGED_PROP_ROTATED_TO_MAX under AIEvent. Construction
// at 0x82738BD8 uses cAIEvent(type 115, source), size 0x44, and primary table
// 0x8213EFFC; slot 1 is 0x82737040. There is no additional payload.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cHingedPropRotatedToMaxEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cHingedPropRotatedToMaxEvent, CD2_SIZE(cHingedPropRotatedToMaxEvent, 0x44))
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cHingedPropRotatedToMaxEvent> g_cHingedPropRotatedToMaxEvent;
