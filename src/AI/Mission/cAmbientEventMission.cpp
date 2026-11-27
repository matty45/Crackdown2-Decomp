// src/AI/Mission/cAmbientEventMission.cpp
//
// Class: cAmbientEventMission (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cAmbientEventMission.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/cAmbientEventMission.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/cAmbientEventMission.cpp

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
#include "AI/cAmbientEventMission.h"
#include "cd2/memory.h"
#include "AI/cMissionManager.h"
#include "AI/cMission.h"
#include "rws/msg.h"
#include "editor/guid_event_handler.h"
#include "Network/SNetGlobalData.h"
#include "Sim/cTimeOfDay.h"

namespace AI
{
    static const char *const pcAmbientEventMissionClassID = "cAmbientEventMission";

    const Fun_Runtime::cClass &cAmbientEventMission::RetClass() const
    {
        return *ms_pcAmbientEventMissionClass;
    }

    bool cAmbientEventMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAmbientEventMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cAmbientEventMission::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAmbientEventMission;
    }

    const char *cAmbientEventMission::RetClassName() const
    {
        return "cAmbientEventMission";
    }

    const Fun_Runtime::cClass *cAmbientEventMission::ms_pcAmbientEventMissionClass = &cAmbientEventMission::StaticCreateClass();

    Fun_Runtime::cClass &cAmbientEventMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientEventMissionClass = new Fun_Runtime::cClass(0x9FE8B, "cAmbientEventMission", 0x3B0);
        return *cAmbientEventMissionClass;
    }

    static RWS::CClassFactory::CRegistrar cAmbientEventMissionRegistrar(
        "cAmbientEventMission", cAmbientEventMission::MakeNew, 0x3B0, false);

    // CD2 0x82F900E0: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAmbientEventMissioncMissionBaseInheritRegistrar(
        AI::cAmbientEventMission::StaticCreateClass(), AI::cMissionBase::StaticCreateClass());

    cAmbientEventMission::~cAmbientEventMission()
    {
        UnLinkMsg(iMsgTODDawn);
        UnLinkMsg(iMsgTODDusk);
    }

    void cAmbientEventMission::HandleEvents(RWS::CMsg &pMsg)
    {
        if (IsAuthority() && m_bActive)
        {
            if (pMsg.Id == iMsgTODDawn)
            {
                m_bIsDay = true;
                IncrementCount();
            }
            if (pMsg.Id == iMsgTODDusk)
            {
                m_bIsDay = false;
                IncrementCount();
            }
        }
    }

    unsigned short cAmbientEventMission::RetMissionID() const
    {
        return cMissionBase::RetMissionID() + cMissionManager::ms_pMissionManager->m_vMissions.size();
    }

    void cAmbientEventMission::InitReplication()
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

    void cAmbientEventMission::TermReplication()
    {
        m_nNodeID = 0xFF;
        SetReplicatedObjectID(0xFFFFFFFF);
        TermReplicatedClass();
        SetNetRole(eNR_None);
    }

    void cAmbientEventMission::Activate()
    {
        cMissionBase::Activate();
        InitReplication();
        if (IsAuthority())
        {
            m_bIsDay = Sim::cTimeOfDay::ms_pInstance->IsDayTime();
            if (m_bIsDay)
                SetAmbientEventDayState(eAES_Day1);
            else
                SetAmbientEventDayState(eAES_Night1);
        }
    }

    void cAmbientEventMission::Deactivate()
    {
        cMissionBase::Deactivate();
        TermReplication();
    }

    void cAmbientEventMission::HandleAttributes(const RWS::CAttributePacket &attr)
    {
        cMissionBase::HandleAttributes(attr);
        for (RWS::CAttributeCommandIterator it(attr, pcAmbientEventMissionClassID); !it.IsFinished(); ++it)
        {
            if (it->GetCommandId() == 0)
            {
                const RWS::RWSGUIDList *pList = it->GetAs_RWSGUIDList();
                unsigned int nNum = pList->Num();
                for (unsigned int i = 0; i < nNum; i++)
                {
                    RWS::RWSGUID guid = pList->GetGUID(i);
                    cMission *pMission = Editor::cGUIDLinker<cMission>::LinkToObject(guid);
                    if (pMission)
                        m_vMissions.push_back(pMission);
                }
            }
        }
        if (attr.IsInstanceCreationPacket())
            m_nMissionIndex = cMissionManager::ms_pMissionManager->RegisterAmbientEventMission(this);
    }

    void cAmbientEventMission::TickUpdate(float dT)
    {
        if (!m_bCleared && m_vMissions.size() != 0)
        {
            bool bAllComplete = true;
            for (cMission **it = m_vMissions.begin(); it != m_vMissions.end(); ++it)
            {
                if (!(*it)->IsComplete())
                {
                    bAllComplete = false;
                    break;
                }
            }
            if (bAllComplete)
                ToggleCleared();
        }
    }

    void cAmbientEventMission::ReplicateInitialFields()
    {
        _AllocateUInt8(static_cast<unsigned char>(m_eDayState), eRF_GlobalEventState, sReplicatedField::WriteReliable);
    }

    void cAmbientEventMission::ReplicateFields()
    {
        unsigned char nDayState = static_cast<unsigned char>(m_eDayState);
        bool bReplicated = ReplicateUInt8(&nDayState, eRF_GlobalEventState);
        if (m_iReadWrite == 199 && bReplicated)
            SetAmbientEventDayState(static_cast<eAmbientEventDayState>(nDayState));
    }
}
