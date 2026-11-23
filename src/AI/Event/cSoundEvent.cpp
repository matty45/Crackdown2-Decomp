// AI/Event/cSoundEvent.cpp: RuffKing's Libraries/Shared/AI/Event/cSoundEvent.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cSoundEventSubscriptionTypeScriptRegistration.h"
#include "AI/cSoundEvent.h"
#include "AI/cWeaponSoundEvent.h"
#include "AI/cBulletSoundEvent.h"
#include "AI/cGrenadeSoundEvent.h"
#include "lua/lua.h"

namespace AI
{
    const char *cSoundEventSubscriptionTypeScriptRegistration::RetName() const
    {
        return "eSoundEventSubscriptionType";
    }

    float cSoundEvent::RetVolume()
    {
        return m_fVolume;
    }

    const Fun_Runtime::cScriptTypeRegistration *cWeaponSoundEvent::RetScriptTypeRegistration() const
    {
        return &g_cWeaponSoundEvent;
    }

    Fun_Runtime::cScriptHost *cWeaponSoundEvent::RetTarget() const
    {
        return m_pTarget;
    }

    bool cWeaponSoundEvent::IsValid()
    {
        return m_pSource != 0 && RetInstigator() != 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cBulletSoundEvent::RetScriptTypeRegistration() const
    {
        return &g_cBulletSoundEvent;
    }

    cCharacterEntityIF *cGrenadeSoundEvent::RetInstigator()
    {
        return m_pActivator;
    }

    void cSoundEventSubscriptionTypeScriptRegistration::RegisterValues(lua_State *state)
    {
        lua_pushliteral(state, "nCanHear");
        lua_pushnumber(state, 0.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "nConcerns");
        lua_pushnumber(state, 1.0f);
        lua_settable(state, -3);
    }

    // CD2 0x82F7A500 registers this four-byte enum object at 0x83818A58.
    static cSoundEventSubscriptionTypeScriptRegistration g_cSoundEventSubscriptionTypeScriptRegistration;
}
