// STAND-IN: descriptive class/global names follow AIE_INTERESTING_OBJECT (initializer 0x82F783C0).
// CD2 constructor 0x823EC538 calls cAIEvent, copies an object safe pointer into +0x44, then installs
// primary table 0x820FBFB0 (slot 1: 0x823EC608). Registrar method 0x8243E028 names its getter RetObject;
// cNonGameBase is the shared game-object type used by that script-return wrapper.
#ifndef AI_CINTERESTINGOBJECTEVENT_H
#define AI_CINTERESTINGOBJECTEVENT_H
#include "AI/cAIEvent.h"
#include "gom/non_game_base.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cInterestingObjectEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual void Slot5();
        virtual bool IsValid();
    protected:
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pObject;
        CD2_LAYOUT_CHECKS(cInterestingObjectEvent,
            CD2_SIZE(cInterestingObjectEvent, 0x54)
            CD2_OFFSET(cInterestingObjectEvent, m_pObject, 0x44))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cInterestingObjectEvent> g_cInterestingObjectEvent; // CD2 0x83817890
#endif
