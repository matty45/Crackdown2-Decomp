// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cBeaconMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "SaveGame/cLoadStream.h"
#include "Crowd/cCrowdCD2.h"

namespace AI
{
    const Fun_Runtime::cClass *cBeaconMission::ms_pcBeaconMissionClass = &cBeaconMission::StaticCreateClass();

    cBeaconMission::cBeaconMission() {}

    const Fun_Runtime::cClass &cBeaconMission::RetClass() const
    {
        return *ms_pcBeaconMissionClass;
    }

    const char *cBeaconMission::RetClassName() const
    {
        return "cBeaconMission";
    }

    bool cBeaconMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBeaconMissionClass->IsA(c);
    }

    void cBeaconMission::NotifySquadDead(Activity::cSquadSpawnPoint *)
    {
        ++m_nNumInitialSquadsDead;
    }

    RWS::CAttributeHandler *cBeaconMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBeaconMission();
    }
}

static RWS::CClassFactory::CRegistrar cBeaconMissionRegistrar(
    "cBeaconMission", AI::cBeaconMission::MakeNew, 0x2300, false);

namespace AI
{
    Fun_Runtime::cClass &cBeaconMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBeaconMissionClass = new Fun_Runtime::cClass(0x205C3, "cBeaconMission", 0x2300);
        return *cBeaconMissionClass;
    }

    // CD2 0x82F88C20: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBeaconMissioncMissionInheritRegistrar(
        AI::cBeaconMission::StaticCreateClass(), AI::cMission::StaticCreateClass());

    void cBeaconMission::OnLeaveGlobalMissionState(etGlobalMissionState nState)
    {
        switch (nState)
        {
        case eGMS_Complete:
            if (m_pActivationZone)
                m_pActivationZone->Hide();
            break;
        case eGMS_Incomplete:
            for (Fun_Runtime::cVector<cMissionActivationCylinder *>::iterator it = m_vContainmentZones.begin();
                 it != m_vContainmentZones.end(); ++it)
                (*it)->TermTriggerZone();
            break;
        }
    }

    void cBeaconMission::OnClientMissionStateNotification(unsigned char nMissionState, unsigned char)
    {
        switch (m_eMissionState)
        {
        case eBMS_RaisingWFDRT:
        case eBMS_ChargingBeacon:
        case eBMS_ChargingSWGT:
            if (nMissionState == eBMS_RaisingWFDRT)
                SetMissionState(eBMS_Failed, true);
            break;
        case eBMS_EnRoute:
            if (nMissionState == eBMS_EnRoute)
                SetMissionState(eBMS_Dropping, true);
            break;
        }
    }

    void cBeaconMission::Load(SaveGame::cLoadStream *pStream)
    {
        pStream->Read(&m_fLastMissionPhase, 4);
        pStream->Read(&m_fMissionCompletePhase, 4);
        pStream->Read(&m_nNumDaysPassed, 4);
        pStream->Read(&m_nPhase2SpecialCaseSpawnSkip, 4);
        pStream->Read(&m_nPhase3SpecialCaseExtraDay, 4);
        if (m_nNumDaysPassed != -1000 && gpCCD2 && !m_zonesInitialised)
        {
            SetBeaconZones(m_nNumDaysPassed + m_nPhase2SpecialCaseSpawnSkip + m_nPhase3SpecialCaseExtraDay);
            LinkToTrafficZones();
            m_zonesInitialised = true;
            m_validLoadedData = true;
        }
        cMission::Load(pStream);
    }

    void cBeaconMission::NotifyDeliveryStart(int nHeliID)
    {
        m_nHeliID = nHeliID;
        if (nHeliID != 0)
            SetMissionState(eBMS_EnRoute, true);
        else
            SetMissionState(eBMS_AbortDelivery, true);
    }

    void cBeaconMission::NotifyDeliveryFinish(bool bSuccess)
    {
        if (!bSuccess && m_eMissionState != eBMS_Resetting)
            ResetMission();
    }
}
