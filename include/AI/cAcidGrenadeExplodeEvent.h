// STAND-IN: descriptive C++ name is ours. CD2 0x82F78788 registers descriptor
// 0x83817A1C as AIE_ACID_GRENADE_EXPLODE under AIEvent. Construction ending
// at 0x8261D574 uses cAIEvent(type 144, source), size 0x44, and primary table
// 0x82123E00; slot 1 is 0x8261D238. There is no additional payload.
#pragma once
#include "AI/cAIEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cAcidGrenadeExplodeEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        CD2_LAYOUT_CHECKS(cAcidGrenadeExplodeEvent, CD2_SIZE(cAcidGrenadeExplodeEvent, 0x44))
    };
}
// The descriptor initializer is outside the scaffolded splits.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cAcidGrenadeExplodeEvent> g_cAcidGrenadeExplodeEvent;
