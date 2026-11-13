// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cBreachHoleMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "PLAYER/cPlayer.h"

namespace AI
{
    const Fun_Runtime::cClass *cBreachHoleMission::ms_pcBreachHoleMissionClass = &cBreachHoleMission::StaticCreateClass();

    cBreachHoleMission::cBreachHoleMission() {}

    const Fun_Runtime::cClass &cBreachHoleMission::RetClass() const
    {
        return *ms_pcBreachHoleMissionClass;
    }

    const char *cBreachHoleMission::RetClassName() const
    {
        return "cBreachHoleMission";
    }

    bool cBreachHoleMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBreachHoleMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBreachHoleMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBreachHoleMission();
    }

    static RWS::CClassFactory::CRegistrar cBreachHoleMissionRegistrar(
        "cBreachHoleMission", cBreachHoleMission::MakeNew, 0x530, false);

    Fun_Runtime::cClass &cBreachHoleMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBreachHoleMissionClass = new Fun_Runtime::cClass(0x9EFED, "cBreachHoleMission", 0x530);
        return *cBreachHoleMissionClass;
    }

    // CD2 0x82F89E38: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBreachHoleMissioncMissionInheritRegistrar(
        AI::cBreachHoleMission::StaticCreateClass(), AI::cMission::StaticCreateClass());

    void cBreachHoleMission::ResetMission()
    {
        if (IsAuthority())
        {
            SetMissionState(eBS_Closed, true);
            m_fCurrentTimer = 0.0f;
        }
    }

    void cBreachHoleMission::Activate()
    {
        if (m_pActivationZone)
            m_pActivationZone->InitTriggerZone();
        m_eMissionState = eBS_Closed;
        cMission::Activate();
    }

    void cBreachHoleMission::Deactivate()
    {
        if (m_pActivationZone)
            m_pActivationZone->TermTriggerZone();
        cMission::Deactivate();
    }

    void cBreachHoleMission::GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState)
    {
        switch (nMissionState)
        {
        case eBS_Open:
        case eBS_Standby:
        case eBS_FailedToOpen:
        case eBS_Closed:
            nMissionState = eBS_Closed;
            break;
        case eBS_Destroyed:
        case eBS_ChopperClosing:
            nMissionState = eBS_Destroyed;
            break;
        default:
            nGlobalMissionState = m_eGlobalMissionState;
            nMissionState = m_eMissionState;
            break;
        }
    }

    void cBreachHoleMission::OnTransitionMissionState(unsigned char nNewMissionState)
    {
        m_ePrevMissionState = m_eMissionState;
        m_eMissionState = nNewMissionState;
    }

    void cBreachHoleMission::NotifyDeliveryStart(int nHeliID)
    {
        m_nHeliID = nHeliID;
    }

    bool cBreachHoleMission::IsLocalPlayerNearby() const
    {
        if (m_pActivationZone)
        {
            CHARACTER::cCharacter *pCharacter = PLAYER::cPlayer::RetLocalPlayerCharacter();
            if (pCharacter)
                return m_pActivationZone->IsWithin(pCharacter);
        }
        return false;
    }
}
