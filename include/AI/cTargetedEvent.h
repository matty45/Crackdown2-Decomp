// STAND-IN: descriptive class/global names follow AIE_TARGETED (initializer 0x82F78100).
// CD2 construction at 0x823EF9D8 calls cAIEvent, then installs table 0x820FBF8C (slot 1: 0x823EC528).
// The safe pointer at +0x44 takes the character controller at +0x1520 (RuffKing: m_pController,
// cCharacterInterface *); registration 0x8243DF08 names its getter RetTargeter.
#ifndef AI_CTARGETEDEVENT_H
#define AI_CTARGETEDEVENT_H
#include "AI/cAIEvent.h"
#include "CHARACTER/cCharacterInterface.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cTargetedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    protected:
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacterInterface> m_pTargeter;
        CD2_LAYOUT_CHECKS(cTargetedEvent,
            CD2_SIZE(cTargetedEvent, 0x54)
            CD2_OFFSET(cTargetedEvent, m_pTargeter, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cTargetedEvent> g_cTargetedEvent; // CD2 0x83817770
#endif
