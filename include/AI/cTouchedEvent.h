// STAND-IN: descriptive class/global names follow AIE_TOUCHED (initializer 0x82F79E10).
// CD2 construction at 0x82360258 calls cAIEvent, builds a safe pointer at +0x44 in a 0x54-byte object,
// and installs table 0x820FC0B4 (slot 1: 0x823EC880). Registration 0x82440280 names its getter RetToucher.
// The pointee is represented by its shared cNonGameBase interface; its narrower dynamic type is unresolved.
#ifndef AI_CTOUCHEDEVENT_H
#define AI_CTOUCHEDEVENT_H
#include "AI/cAIEvent.h"
#include "gom/non_game_base.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTouchedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual Fun_Runtime::Vec3 RetPosition() const;
        virtual void Slot5();
        virtual bool IsValid();
    protected:
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pToucher;
        CD2_LAYOUT_CHECKS(cTouchedEvent,
            CD2_SIZE(cTouchedEvent, 0x54)
            CD2_OFFSET(cTouchedEvent, m_pToucher, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTouchedEvent> g_cTouchedEvent; // CD2 0x83818940
#endif
