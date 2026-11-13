// Partial DamageEvents object. CD2 0x82441688 registers cDamageTakenEvent's payload getters;
// names agree with RuffKing AI/Event/DamageEvents.h/.cpp. Three adjacent damage-enum
// registrars follow this object's header-constant run at 0x82F7A9C0..0x82F7ACD0.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cDamageTakenEvent.h"
#include "AI/cDamageTypeScriptRegistration.h"
#include "AI/cDamageImpactTypeScriptRegistration.h"
#include "AI/cDamageSubTypeScriptRegistration.h"

namespace AI
{
    const char *cDamageTypeScriptRegistration::RetName() const
    {
        return "eDamageType";
    }

    const char *cDamageImpactTypeScriptRegistration::RetName() const
    {
        return "eDamageImpactType";
    }

    const char *cDamageSubTypeScriptRegistration::RetName() const
    {
        return "eDamageSubType";
    }

    float cDamageTakenEvent::RetAmount()
    {
        return m_fAmount;
    }

    Fun_Runtime::Vec3 cDamageTakenEvent::RetHitDirection()
    {
        // CD2 returns only the spatial components and supplies w=1 independently of the stored fourth component.
        return Fun_Runtime::Vec3(m_vecHitDirection.x, m_vecHitDirection.y, m_vecHitDirection.z);
    }

    Fun_Runtime::Vec3 cDamageTakenEvent::RetHitLocation()
    {
        return Fun_Runtime::Vec3(m_vecHitLocation.x, m_vecHitLocation.y, m_vecHitLocation.z);
    }

    unsigned int cDamageTakenEvent::RetDamageImpactType()
    {
        return m_eDamageImpactType;
    }

    // CD2 0x82F7ACD0: eDamageType object at 0x83818CCC, table 0x82100468.
    static cDamageTypeScriptRegistration g_cDamageTypeScriptRegistration;

    // CD2 0x82F7AD18: eDamageImpactType object at 0x83818CD0, table 0x82100474.
    static cDamageImpactTypeScriptRegistration g_cDamageImpactTypeScriptRegistration;

    // CD2 0x82F7AD60: eDamageSubType object at 0x83818CD4, table 0x82100480.
    static cDamageSubTypeScriptRegistration g_cDamageSubTypeScriptRegistration;
}
