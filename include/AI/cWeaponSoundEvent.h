// STAND-IN: reference class/base/member names. CD2 constructor 0x82440A28 installs table 0x821001CC,
// builds the target safe pointer at +0x48 and copies the start/end vectors to +0x60/+0x70.
// CD2's target is a script-host pointer: constructor stores it directly and RetTarget (0x824404E0)
// returns the payload without adjustment. Initializer 0x82F7A5F8 registers AIE_WEAPON_SOUND at 0x83818AA4.
#ifndef AI_CWEAPONSOUNDEVENT_H
#define AI_CWEAPONSOUNDEVENT_H
#include "AI/cSoundEvent.h"
#include "fun_runtime/script_type_registrar.h"
namespace AI
{
    class cWeaponSoundEvent : public cSoundEvent
    {
    public:
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual bool IsValid();
        virtual bool CanHearThisSound(cCharacterEntityIF *);
        virtual Fun_Runtime::Vec3 RetScriptPosition() const;
        virtual cCharacterEntityIF *RetInstigator();
        virtual bool Concerns(cNonGameBase *);
    protected:
        virtual float RetDistance(const Fun_Runtime::Vec3 &);
        Fun_Runtime::cSafeDeletablePointer<Fun_Runtime::cScriptHost> m_pTarget;
        Fun_Runtime::Vec3 m_vecStart;
        Fun_Runtime::Vec3 m_vecEnd;
        CD2_LAYOUT_CHECKS(cWeaponSoundEvent,
            CD2_SIZE(cWeaponSoundEvent, 0x80)
            CD2_OFFSET(cWeaponSoundEvent, m_pTarget, 0x48)
            CD2_OFFSET(cWeaponSoundEvent, m_vecStart, 0x60)
            CD2_OFFSET(cWeaponSoundEvent, m_vecEnd, 0x70))
    };
}
extern Fun_Runtime::cScriptTypeRegistrar<AI::cWeaponSoundEvent> g_cWeaponSoundEvent;
#endif
