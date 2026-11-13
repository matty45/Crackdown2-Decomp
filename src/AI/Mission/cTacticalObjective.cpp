// AI/Mission/cTacticalObjective.cpp: RuffKing's Libraries/Shared/AI/Mission/cTacticalObjective.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cHeliDropPoint.h"
#include "AI/cTacticalObjective.h"
#include "cd2/memory.h"
#include "Network/SNetGlobalData.h"

namespace AI
{
    static RWS::CClassFactory::CRegistrar cHeliDropPointRegistrar(
        "cHeliDropPoint", cHeliDropPoint::MakeNew, 0x80, false);

    const Fun_Runtime::cClass &cHeliDropPoint::RetClass() const
    {
        return *ms_pcHeliDropPointClass;
    }

    bool cHeliDropPoint::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHeliDropPointClass->IsA(c);
    }

    const char *cHeliDropPoint::RetClassName() const
    {
        return "cHeliDropPoint";
    }

    bool cTacticalObjective::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTacticalObjectiveClass->IsA(c);
    }

    RWS::CAttributeHandler *cTacticalObjective::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTacticalObjective;
    }

    const char *cTacticalObjective::RetClassName() const
    {
        return "cTacticalObjective";
    }

    void cTacticalObjective::Destruct()
    {
        this->~cTacticalObjective();
    }

    bool cTacticalObjective::IsComplete() const
    {
        return m_eMissionState >= eTOS_Complete;
    }

    bool cTacticalObjective::HasBackupBeenCalled() const
    {
        return m_eMissionState >= eTOS_Backup;
    }

    void cHeliDropPoint::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        HandleSystemCommands(packet);
        if (packet.IsInstanceCreationPacket())
            m_EventHandler.Register(this, packet.GetInstanceId());
    }

    Fun_Runtime::cClass &cTacticalObjective::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTacticalObjectiveClass = new Fun_Runtime::cClass(0x9F3D5, "cTacticalObjective", 0x530);
        return *cTacticalObjectiveClass;
    }

    const Fun_Runtime::cClass *cTacticalObjective::ms_pcTacticalObjectiveClass = &cTacticalObjective::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTacticalObjectivecMissionInheritRegistrar(
        cTacticalObjective::StaticCreateClass(), cMission::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTacticalObjectiveRegistrar(
        "cTacticalObjective", cTacticalObjective::MakeNew, 0x530, false);

    void cTacticalObjective::InitReplication()
    {
        if (Network::IsHost())
        {
            m_nNodeID = Network::RetLocalNodeID();
            SetReplicatedObjectID(RetMissionID());
            InitReplicatedClass(this, false);
            SetNetRole(eNR_Authority);
        }
        else
            SetNetRole(eNR_DumbProxy);
    }

    void cTacticalObjective::TermReplication()
    {
        m_nNodeID = 0xFF;
        SetReplicatedObjectID(0xFFFFFFFF);
        if (m_bRegisteredWithReplicationManager)
            TermReplicatedClass();
        SetNetRole(eNR_None);
    }

    void cTacticalObjective::OnLeaveGlobalMissionState(etGlobalMissionState nState)
    {
        if (nState == eGMS_Incomplete)
        {
            if (m_pActivationZone)
                m_pActivationZone->Hide();
            if (m_pContainmentZone)
                m_pContainmentZone->TermTriggerZone();
        }
    }

    void cTacticalObjective::GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState)
    {
        switch (nMissionState)
        {
        case eTOS_Inactive:
        case eTOS_InTO:
        case eTOS_Backup:
            nMissionState = eTOS_Inactive;
            break;
        case eTOS_AwaitingDrop:
        case eTOS_DropCameraCut:
        case eTOS_Complete:
            nMissionState = eTOS_Complete;
            break;
        default:
            nGlobalMissionState = m_eGlobalMissionState;
            nMissionState = m_eMissionState;
            break;
        }
    }

    void cTacticalObjective::NotifyDeliveryStart(int nHeliID)
    {
        if (m_eMissionState != eTOS_DropCameraCut)
        {
            m_nHeliID = nHeliID;
            SetMissionState(eTOS_DropCameraCut, true);
        }
    }

    void cTacticalObjective::NotifyDeliveryFinish(bool)
    {
        if (m_eMissionState != eTOS_Complete)
        {
            if (++m_nNumDrops >= m_vHeliDropPoints.size())
            {
                m_nNumDrops = 0;
                SetMissionState(eTOS_Complete, true);
            }
        }
    }

    bool cTacticalObjective::IsLocalPlayerNearby() const
    {
        return IsLocalPlayerInsideInner();
    }
}
