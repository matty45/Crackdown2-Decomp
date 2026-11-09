// STAND-IN: reference name/base/member. CD2 construction at 0x8234BAD0 calls cSoundEvent, then builds
// the enemy safe pointer at +0x48 and installs primary table 0x820FB198 (slot 1: 0x823E7BF8).
// Initializer 0x82F7A8B8 registers AIE_DANGER_VOCAL under AIE_SOUND at 0x83818BC4.
#ifndef AI_CDANGERVOCALEVENT_H
#define AI_CDANGERVOCALEVENT_H
#include "AI/cSoundEvent.h"
#include "AI/cCharacterEntityIF.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cDangerVocalEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool Concerns(cNonGameBase *);
    protected:
        Fun_Runtime::cSafeDeletablePointer<cCharacterEntityIF> m_pEnemy;
        CD2_LAYOUT_CHECKS(cDangerVocalEvent,
            CD2_SIZE(cDangerVocalEvent, 0x58)
            CD2_OFFSET(cDangerVocalEvent, m_pEnemy, 0x48))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cDangerVocalEvent> g_cDangerVocalEvent;
#endif
