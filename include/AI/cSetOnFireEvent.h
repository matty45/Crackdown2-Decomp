// STAND-IN: descriptive class/global names follow AIE_SET_ON_FIRE (initializer 0x82F7B228).
// CD2 construction at 0x823EF7D8 calls cAIEvent, builds a safe pointer at +0x44 and installs
// primary table 0x820FC06C (slot 1: 0x823EC860). Script registration 0x8243E1A8 calls its getter
// RetInstigator; the reference event instigators and its shared script return wrapper use cCharacterEntityIF.
#ifndef AI_CSETONFIREEVENT_H
#define AI_CSETONFIREEVENT_H
#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cSetOnFireEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pInstigator;
        CD2_LAYOUT_CHECKS(cSetOnFireEvent,
            CD2_SIZE(cSetOnFireEvent, 0x54)
            CD2_OFFSET(cSetOnFireEvent, m_pInstigator, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cSetOnFireEvent> g_cSetOnFireEvent; // CD2 0x83818E00
#endif
