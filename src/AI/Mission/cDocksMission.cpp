// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cDocksMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cDocksMission::RetClassName() const
    {
        return "cDocksMission";
    }

    static RWS::CClassFactory::CRegistrar cDocksMissionRegistrar(
        "cDocksMission", cDocksMission::MakeNew, 0x450, false);

    Fun_Runtime::cClass &cDocksMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cDocksMissionClass = new Fun_Runtime::cClass(0x9F4FE, "cDocksMission", 0x450);
        return *cDocksMissionClass;
    }

    const Fun_Runtime::cClass *cDocksMission::ms_pcDocksMissionClass = &cDocksMission::StaticCreateClass();

    const Fun_Runtime::cClass &cDocksMission::RetClass() const
    {
        return *ms_pcDocksMissionClass;
    }

    bool cDocksMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcDocksMissionClass->IsA(c);
    }

    // CD2 0x82F8A480: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cDocksMissioncMissionInheritRegistrar(
        AI::cDocksMission::StaticCreateClass(), AI::cMission::StaticCreateClass());

    void cDocksMission::Activate()
    {
        m_eMissionState = eDMS_Inactive;
        SetAssociatedZonesEnabled(true);
        cMission::Activate();
        SetSquadGroup(eSG_B);
    }

    void cDocksMission::Deactivate()
    {
        SetAssociatedZonesEnabled(false);
        cMission::Deactivate();
    }

    void cDocksMission::TickUpdate(float)
    {
        if (IsAuthority())
            Update();
        CheckForCameraCutActivation();
        CheckForCameraCutDeactivation();
    }

    void cDocksMission::GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState)
    {
        switch (nMissionState)
        {
        default:
            nGlobalMissionState = m_eGlobalMissionState;
            nMissionState = m_eMissionState;
            break;
        case eDMS_CallingDrop:
        case eDMS_AwaitingDelivery:
        case eDMS_Complete:
            nMissionState = eDMS_Complete;
            break;
        case eDMS_Inactive:
            nMissionState = eDMS_Inactive;
            break;
        }
    }

    void cDocksMission::ResetMission()
    {
        if (m_nHeliID)
            m_nHeliID = 0;
        SetMissionState(eDMS_Inactive, true);
    }

    unsigned int cDocksMission::NumAssociatedMissionsComplete()
    {
        unsigned int nComplete = 0;
        for (cMission **it = m_vMissions.begin(); it != m_vMissions.end(); ++it)
        {
            if ((*it)->IsComplete())
                ++nComplete;
        }
        return nComplete;
    }

    void cDocksMission::NotifyDeliveryStart(int nHeliID)
    {
        m_nHeliID = nHeliID;
    }

    void cDocksMission::NotifyDeliveryFinish(bool)
    {
        SetMissionState(eDMS_Complete, true);
    }

    void cDocksMission::NotifyDeliveryDrop(bool bSuccess)
    {
        if (bSuccess)
            SetMissionState(eDMS_Complete, true);
    }

    bool cDocksMission::IsLocalPlayerNearby() const
    {
        for (cMission *const *it = m_vMissions.begin(); it != m_vMissions.end(); ++it)
        {
            if (*it && (*it)->IsLocalPlayerNearby())
                return true;
        }
        return false;
    }
}
