// src/Vehicle/cLandVehicle.cpp: Vehicle::cLandVehicle (include/Vehicle/cLandVehicle.h). Definitions follow CD2's order:
// the static registrars' initializers (0x82FE8990..0x82FE8A70), then the functions from 0x826C0DB8.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Vehicle/cLandVehicle.h"
#include "PHYSICS/cCustomVehicleInstance.h"
#include "Havok/hkVehicleDriverInputAnalogStatus.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include "VFX/cAfterlightRounded.h"
#include "VFX/cGlobalLightManager.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cLandVehicle::ms_pcLandVehicleClass = &cLandVehicle::StaticCreateClass();

    // CD2 0x82FE89B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cLandVehiclecVehicleInheritRegistrar(
        cLandVehicle::StaticCreateClass(), cVehicle::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cLandVehicleRegistrar(
        "cLandVehicle", cLandVehicle::MakeNew, 0x28C0, false);

    // CD2 0x82FE8A70: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cLandVehicleSpawningRegistrar(
        cLandVehicle::StaticCreateClass(), cLandVehicle::SpawnFromPrototype);

    const Fun_Runtime::cClass &cLandVehicle::RetClass() const
    {
        return *ms_pcLandVehicleClass;
    }

    bool cLandVehicle::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcLandVehicleClass->IsA(c);
    }

    RWS::CAttributeHandler *cLandVehicle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cLandVehiclePrototype(packet);
    }

    const char *cLandVehicle::RetClassName() const
    {
        return "cLandVehicle";
    }

    RWS::CAttributeHandler *cLandVehicle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cLandVehicle;
        return 0;
    }

    Fun_Runtime::cClass &cLandVehicle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLandVehicleClass = new Fun_Runtime::cClass(0x642, "cLandVehicle", 0x28C0);
        return *cLandVehicleClass;
    }

    void cLandVehicle::AddVehicleLights()
    {
        if (VFX::cGlobalLightManager::ms_pSingleton)
        {
            cLandVehiclePrototype *pProto = static_cast<cLandVehiclePrototype *>(m_pPrototype);
            AddVehicleLight(m_apHeadLightLargeVFX, m_aHeadLightLargeInfo, 6, pProto->m_nLightType[eVLT_Headlight_Large]);
            AddVehicleLight(m_apHeadLightSmallVFX, m_aHeadLightSmallInfo, 4, pProto->m_nLightType[eVLT_Headlight_Small]);
            AddVehicleLight(m_apTailLightVFX, m_aTailLightInfo, 4, pProto->m_nLightType[eVLT_TailLight]);
            AddVehicleLight(m_apReverseLightVFX, m_aReverseLightInfo, 4, pProto->m_nLightType[eVLT_ReverseLight]);
            AddVehicleLight(m_apBreakLightVFX, m_aBreakLightInfo, 4, pProto->m_nLightType[eVLT_BreakLight]);
            AddVehicleLight(m_apPoliceLightRedVFX, m_aPoliceLightRedInfo, 4, pProto->m_nLightType[eVLT_PoliceLightRed]);
            AddVehicleLight(m_apPoliceLightBlueVFX, m_aPoliceLightBlueInfo, 4, pProto->m_nLightType[eVLT_PoliceLightBlue]);
            AddVehicleLight(m_apPoliceLightFrontVFX, m_PoliceHoodLightFrontInfo, 3, pProto->m_nLightType[eVLT_PoliceLightBlue]);
            AddVehicleLight(m_apPoliceLightBackVFX, m_PoliceHoodLightBackInfo, 3, pProto->m_nLightType[eVLT_PoliceLightRed]);
        }
    }

    bool cLandVehicle::IsFunctionallyDamaged()
    {
        if (!IsEngineActive() || m_bBlownUp || m_DamageEffect.IsAWheelDamaged())
            return true;
        return false;
    }

    bool cLandVehicle::CanTurnOnPoliceLights()
    {
        return RetPoliceLightsActivated() && (m_nNGBFlags & 2) && IsInViewFrustum();
    }

    bool cLandVehicle::CanTurnOnExhaustFumes()
    {
        return IsEngineActive() && (m_nNGBFlags & 2) && IsInViewFrustum() && RetPhysicsLOD() <= 2;
    }

    void cLandVehicle::FullySubmergedEvent()
    {
        if (static_cast<cVehiclePrototype *>(m_pPrototype)->m_eVehicleType != eVT_SUV)
            StopEngine();
    }

    bool cLandVehicle::IsReversing()
    {
        return m_pVehicleInstance ? bool(m_pVehicleInstance->IsReversing()) : false;
    }

    bool cLandVehicle::IsBraking()
    {
        return m_pVehicleInstance ? bool(m_pVehicleInstance->IsBraking()) : false;
    }

    bool cLandVehicle::IsHandbrakeOn()
    {
        return m_pVehicleInstance ? bool(static_cast<hkVehicleDriverInputAnalogStatus *>(m_pVehicleInstance->m_deviceStatus)->m_handbrakeButtonPressed == true) : false;
    }

    void cLandVehicle::SetEngineDamage(float modifier)
    {
        if (m_pVehicleInstance)
            m_pVehicleInstance->m_DamageTorqueEfficiencyMultiplier = modifier;
    }

    float cLandVehicle::RetEngineDamage()
    {
        if (m_pVehicleInstance)
            return m_pVehicleInstance->m_DamageTorqueEfficiencyMultiplier;
        return Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1;
    }

    void cLandVehicle::SetSteeringAngle(float angle)
    {
        if (m_pVehicleInstance)
            m_pVehicleInstance->SetSteeringAngle(angle);
    }

    bool cLandVehicle::IsAPoliceVehicle()
    {
        return static_cast<cLandVehiclePrototype *>(m_pPrototype)->m_bIsPoliceVehicle;
    }

    void cLandVehicle::TurnOffPoliceLights(bool bForce)
    {
        if (IsAPoliceVehicle() && (m_bPoliceLightsOn || bForce))
        {
            cVehicle::TurnOffVehicleLights(m_apPoliceLightRedVFX, m_aPoliceLightRedInfo, 4);
            cVehicle::TurnOffVehicleLights(m_apPoliceLightBlueVFX, m_aPoliceLightBlueInfo, 4);
            cVehicle::TurnOffVehicleLights(m_apPoliceLightFrontVFX, m_PoliceHoodLightFrontInfo, 3);
            cVehicle::TurnOffVehicleLights(m_apPoliceLightBackVFX, m_PoliceHoodLightBackInfo, 3);
            m_bPoliceLightsOn = false;
        }
    }

    void cLandVehicle::ActivateVehicleLights(bool bActivate)
    {
        m_bVehicleLightsActivated = bActivate;
        if (CanTurnOnVehicleLights())
            TurnOnVehicleLights();
        else
            TurnOffVehicleLights(false);
    }

    void cLandVehicle::TurnOnVehicleLights()
    {
        if (!m_bLightsOn)
        {
            TurnOnVehicleLight(m_apHeadLightLargeVFX, m_aHeadLightLargeInfo, 6, eVLT_Headlight_Large);
            TurnOnVehicleLight(m_apHeadLightSmallVFX, m_aHeadLightSmallInfo, 4, eVLT_Headlight_Small);
            TurnOnVehicleLight(m_apTailLightVFX, m_aTailLightInfo, 4, eVLT_TailLight);
            TurnOnAfterlights();
            m_LastUpdateTimestamp = -1;
            m_bLightsOn = true;
        }
    }

    void cLandVehicle::TurnOffVehicleLights(bool bForce)
    {
        if (m_bLightsOn || bForce)
        {
            cVehicle::TurnOffVehicleLights(m_apHeadLightLargeVFX, m_aHeadLightLargeInfo, 6);
            cVehicle::TurnOffVehicleLights(m_apHeadLightSmallVFX, m_aHeadLightSmallInfo, 4);
            cVehicle::TurnOffVehicleLights(m_apTailLightVFX, m_aTailLightInfo, 4);
            cVehicle::TurnOffVehicleLights(m_apReverseLightVFX, m_aReverseLightInfo, 4);
            cVehicle::TurnOffVehicleLights(m_apBreakLightVFX, m_aBreakLightInfo, 4);
            VFX::FreeALRounded(&m_pHeadlight[0]);
            VFX::FreeALRounded(&m_pHeadlight[1]);
            m_bLightsOn = false;
        }
    }

    void cLandVehicle::ResetDamagedLights()
    {
        for (int i = 0; i < 6; i++)
        {
            if (m_apHeadLightLargeVFX[i])
                m_apHeadLightLargeVFX[i]->ResetDamage();
        }
        for (int i = 0; i < 4; i++)
        {
            if (m_apHeadLightSmallVFX[i])
                m_apHeadLightSmallVFX[i]->ResetDamage();
        }
        for (int i = 0; i < 4; i++)
        {
            if (m_apTailLightVFX[i])
                m_apTailLightVFX[i]->ResetDamage();
        }
        for (int i = 0; i < 4; i++)
        {
            if (m_apReverseLightVFX[i])
                m_apReverseLightVFX[i]->ResetDamage();
        }
        for (int i = 0; i < 4; i++)
        {
            if (m_apBreakLightVFX[i])
                m_apBreakLightVFX[i]->ResetDamage();
        }
    }

    void cLandVehicle::SetMustStop(bool mustStop)
    {
        m_bMustStop = mustStop;
    }

    Fun_Runtime::RetVal cLandVehicle::cLandVehiclePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cLandVehicle::CustomiseShape(hkShape **ppCollisionShape)
    {
        CustomiseShape(ppCollisionShape, m_pVehicleData);
    }
}
