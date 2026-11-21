// STAND-IN: reference class/base/member names. CD2 constructor 0x82440B00 installs table 0x8210020C,
// builds the target safe pointer at +0x48 and copies the start/end vectors to +0x60/+0x70.
// Its target uses the same script-host pointer representation as cWeaponSoundEvent.
// Initializer 0x82F7A650 registers AIE_BULLET_SOUND under AIE_SOUND at 0x83818AC8.
#ifndef AI_CBULLETSOUNDEVENT_H
#define AI_CBULLETSOUNDEVENT_H
#include "AI/cSoundEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cBulletSoundEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool CanHearThisSound(cCharacterEntityIF *);
        virtual Fun_Runtime::Vec3 RetScriptPosition() const;
        virtual bool Concerns(cNonGameBase *);
    protected:
        virtual float RetDistance(const Fun_Runtime::Vec3 &);
        Fun_Runtime::cSafeDeletablePointer<Fun_Runtime::cScriptHost> m_pTarget;
        Fun_Runtime::Vec3 m_vecStart;
        Fun_Runtime::Vec3 m_vecEnd;
        CD2_LAYOUT_CHECKS(cBulletSoundEvent,
            CD2_SIZE(cBulletSoundEvent, 0x80)
            CD2_OFFSET(cBulletSoundEvent, m_pTarget, 0x48)
            CD2_OFFSET(cBulletSoundEvent, m_vecStart, 0x60)
            CD2_OFFSET(cBulletSoundEvent, m_vecEnd, 0x70))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cBulletSoundEvent> g_cBulletSoundEvent;
#endif
