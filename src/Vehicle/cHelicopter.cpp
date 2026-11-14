// src/Vehicle/cHelicopter.cpp: Vehicle::cHelicopter (include/Vehicle/cHelicopter.h). Definitions follow CD2's order: the
// static registrars' initializers (0x82FE84C0..0x82FE85A0), then the functions from 0x826B8A78.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Vehicle/cHelicopter.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"
#include <new>

namespace Vehicle
{
    const Fun_Runtime::cClass *cHelicopter::ms_pcHelicopterClass = &cHelicopter::StaticCreateClass();

    // CD2 0x82FE84E8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHelicoptercVehicleInheritRegistrar(
        cHelicopter::StaticCreateClass(), cVehicle::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cHelicopterRegistrar(
        "cHelicopter", cHelicopter::MakeNew, 0x2DB0, false);

    // CD2 0x82FE85A0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHelicopterSpawningRegistrar(
        cHelicopter::StaticCreateClass(), cHelicopter::SpawnFromPrototype);

    const Fun_Runtime::cClass &cHelicopter::RetClass() const
    {
        return *ms_pcHelicopterClass;
    }

    bool cHelicopter::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHelicopterClass->IsA(c);
    }

    RWS::CAttributeHandler *cHelicopter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHeliPrototype(packet);
    }

    const char *cHelicopter::RetClassName() const
    {
        return "cHelicopter";
    }

    RWS::CAttributeHandler *cHelicopter::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cHelicopter;
        return 0;
    }

    float cHelicopter::RetTheoreticalMaxMPH()
    {
        return m_pHeliPrototype->m_fMaxThrustVelo * 2.237f;
    }

    cPintleMount *cHelicopter::RetPintleMount(unsigned char nIdx)
    {
        return &m_aTurrets[nIdx];
    }

    Fun_Runtime::cClass &cHelicopter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHelicopterClass = new Fun_Runtime::cClass(0x675, "cHelicopter", 0x2DB0);
        return *cHelicopterClass;
    }

    bool cHelicopter::CheckForReplicationActivation(unsigned int *nRetCode)
    {
        bool bResult = cVehicle::CheckForReplicationActivation(nRetCode);
        if (m_nAttachedObjectIDField && !m_pCarriedObj)
            return false;
        return bResult;
    }

    bool cHelicopter::IsOnGround()
    {
        if (!m_pCarriedObj)
            return cVehicle::IsOnGround();
        return false;
    }

    unsigned char cHelicopter::RetNumPointsOfInterest()
    {
        return m_nPoiCount;
    }

    GOM::cPointOfInterest *cHelicopter::RetPointOfInterest(int nPoint)
    {
        if (nPoint < m_nPoiCount)
            return &m_POI[nPoint];
        return 0;
    }

    void cHelicopter::HandleTryToEnterInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData,
        cNonGameBase *pNonGameBase, bool &bInteractionResult)
    {
        if (pInteractionData->m_nSubItem == 0 || (m_fCurrentArmRot == m_fMinArmRot && m_bDeployArms))
            cVehicle::HandleTryToEnterInteractPermissionQuery(pInteractionData, pNonGameBase, bInteractionResult);
        else
            bInteractionResult = false;
    }

    bool cHelicopter::IsOkToInteract()
    {
        bool bOk = false;
        if (IsUpRight() && IsDoorAngleOk() && !IsSufficientlyInWater() && !IsDrivenByAI() && !IsInFadeToDeleteFinalStage())
            bOk = true;
        return bOk;
    }
}
