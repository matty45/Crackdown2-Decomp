// AI/Mission/cMission.cpp: RuffKing's Libraries/Shared/AI/Mission/cMission.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMission.h"
#include "cd2/memory.h"
#include "AI/cSecondaryObjectivesInfo.h"

namespace AI
{
    RWS::CAttributeHandler *cSecondaryObjectivesInfo::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSecondaryObjectivesInfo;
    }

    const char *cSecondaryObjectivesInfo::RetClassName() const
    {
        return "cSecondaryObjectivesInfo";
    }

    const Fun_Runtime::cClass &cMission::RetClass() const
    {
        return *ms_pcMissionClass;
    }

    bool cMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cMission::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cMission;
    }

    const char *cMission::RetClassName() const
    {
        return "cMission";
    }

    Fun_Runtime::cClass &cMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionClass = new Fun_Runtime::cClass(0x403, "cMission", 0x3C0);
        return *cMissionClass;
    }

    void cMission::EnableCompletion()
    {
        if (IsAuthority() && m_eGlobalMissionState == eGMS_Uncompletable)
            SetGlobalMissionState(eGMS_Incomplete, true);
    }

    void cMission::OnEnterComplete()
    {
        if (m_pParentMission)
            m_pParentMission->OnChildMissionCompleted(this);
    }

    void cMission::OnSquadGroupBlockedMessage(bool bGroupBlocked, unsigned char nNodeID)
    {
        if (m_bUseSquadGroupTransitionManagement && IsAuthority())
        {
            unsigned short nMask = 1 << nNodeID;
            if (bGroupBlocked)
                m_nBlockedNodes |= nMask;
            else
                m_nBlockedNodes &= ~nMask;
        }
    }

    void cMission::ReplicateInitialFields()
    {
        if (m_eGlobalMissionState == eGMS_Invalid)
            SetFieldStateForCurrentNode(sReplicatedField::WriteSkipOnce, 0);
        // CD2 tests the global state again against 0xFF for field 1 (0x8245A278).
        if (m_eGlobalMissionState == 0xFF)
            SetFieldStateForCurrentNode(sReplicatedField::WriteSkipOnce, 1);
        if (!m_bSquadSwitchBlocked)
        {
            SetFieldStateForCurrentNode(sReplicatedField::WriteSkipOnce, 2);
            SetFieldStateForCurrentNode(sReplicatedField::WriteSkipOnce, 3);
        }
        _AllocateUInt8(static_cast<unsigned char>(m_eGlobalMissionState), 0, sReplicatedField::WriteReliable);
        _AllocateUInt8(m_eMissionState, 1, sReplicatedField::WriteReliable);
        if (m_bUseSquadGroupTransitionManagement)
        {
            unsigned char nGroup = static_cast<unsigned char>(m_eActiveSquadGroup);
            g_pActiveReplicationClass->_AllocateBool(m_bSquadSwitchBlocked, 2, sReplicatedField::WriteReliable);
            _AllocateUInt8Bits(nGroup, 3, 4, sReplicatedField::WriteReliable);
        }
        m_ForceReliableThisFrame = 1;
    }

    void cMission::SetCompletionFlag(bool value)
    {
        m_bCompletionFlag = value;
        m_bResetFlag = false;
        if (value && m_pParentMission)
            m_pParentMission->SetCompletionFlag(value);
    }

    void cMission::SetResetFlag(bool value)
    {
        // This source order reproduces CD2's stores in the tail-recursive parent path.
        m_bCompletionFlag = false;
        m_bResetFlag = value;
        if (value && m_pParentMission)
            m_pParentMission->SetResetFlag(value);
    }

}
