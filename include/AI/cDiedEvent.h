// STAND-IN: reference cDiedEvent name/base/member order (AI/Event/DamageEvents.h).
// CD2 constructor 0x823EC790 calls cAIEvent's constructor, builds the killer safe pointer at +0x44,
// stores damage location at +0x54, and installs primary table 0x82002540 (slot 1: 0x823EC830).
#ifndef AI_CDIEDEVENT_H
#define AI_CDIEDEVENT_H
#include "AI/cAIEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cDiedEvent : public cAIEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool ApplyFilter(cAIEventSubscription &);
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pKiller;
        int m_eDamageLocationEnum;
        CD2_LAYOUT_CHECKS(cDiedEvent,
            CD2_SIZE(cDiedEvent, 0x58)
            CD2_OFFSET(cDiedEvent, m_pKiller, 0x44)
            CD2_OFFSET(cDiedEvent, m_eDamageLocationEnum, 0x54))
    };
}
// CD2 0x82F7AFC0 registers AIE_DIED under AIEvent at 0x83818D04; global name is ours.
extern Fun_Runtime::cScriptTypeRegistrar<AI::cDiedEvent> g_cDiedEvent;
#endif
