// STAND-IN: descriptive C++ name is ours. CD2 0x82FF6318 registers descriptor
// 0x8384AF1C as AIE_HINGED_PROP_ROTATED_TO_MIN under AIEvent. Construction
// at 0x82738AA0 uses cAIEvent(type 114, source), size 0x44, and primary table
// 0x8213EFD8; slot 1 is 0x82737030. There is no additional payload.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cHingedPropRotatedToMinEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cHingedPropRotatedToMinEvent, CD2_SIZE(cHingedPropRotatedToMinEvent, 0x44))
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cHingedPropRotatedToMinEvent> g_cHingedPropRotatedToMinEvent;
