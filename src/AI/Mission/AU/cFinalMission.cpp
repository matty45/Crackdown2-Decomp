// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cFinalMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cFinalMission::ms_pcFinalMissionClass = &cFinalMission::StaticCreateClass();

    cFinalMission::cFinalMission() {}

    const Fun_Runtime::cClass &cFinalMission::RetClass() const
    {
        return *ms_pcFinalMissionClass;
    }

    const char *cFinalMission::RetClassName() const
    {
        return "cFinalMission";
    }

    bool cFinalMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcFinalMissionClass->IsA(c);
    }

    void cFinalMission::OnChildMissionCompleted(AI::cMission *)
    {
        ++m_nNumChildMissionsCompleted;
    }

    RWS::CAttributeHandler *cFinalMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFinalMission();
    }

    static RWS::CClassFactory::CRegistrar cFinalMissionRegistrar(
        "cFinalMission", cFinalMission::MakeNew, 0xC50, false);

    Fun_Runtime::cClass &cFinalMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFinalMissionClass = new Fun_Runtime::cClass(0x2A1FD, "cFinalMission", 0xC50);
        return *cFinalMissionClass;
    }

    // CD2 0x82F89330: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cFinalMissioncMissionInheritRegistrar(
        AI::cFinalMission::StaticCreateClass(), AI::cMission::StaticCreateClass());

    void cFinalMission::OnEnterGlobalMissionState(etGlobalMissionState nState)
    {
        switch (nState)
        {
        case eGMS_Complete:
            if (m_pCore1ContainmentZone)
                m_pCore1ContainmentZone->TermTriggerZone();
            if (m_pCore2ContainmentZone)
                m_pCore2ContainmentZone->TermTriggerZone();
            if (m_pCore3ContainmentZone)
                m_pCore3ContainmentZone->TermTriggerZone();
            break;
        case eGMS_Incomplete:
            if (m_pCore1ContainmentZone)
                m_pCore1ContainmentZone->InitTriggerZone();
            if (m_pCore2ContainmentZone)
                m_pCore2ContainmentZone->InitTriggerZone();
            if (m_pCore3ContainmentZone)
                m_pCore3ContainmentZone->InitTriggerZone();
            break;
        }
    }

    void cFinalMission::Load(SaveGame::cLoadStream *pStream)
    {
        cMission::Load(pStream);
    }

    void cFinalMission::Save(SaveGame::cSaveStream *pStream)
    {
        cMission::Save(pStream);
    }

    void cFinalMission::GetSaveStateForMissionState(unsigned char &nGlobalMissionState, unsigned char &nMissionState)
    {
        switch (nMissionState)
        {
        default:
            nGlobalMissionState = m_eGlobalMissionState;
            nMissionState = m_eMissionState;
            break;
        case eFMS_Ready:
        case eFMS_Charging1:
        case eFMS_Charging2:
        case eFMS_Charging3:
        case eFMS_Collapse:
        case eFMS_Detonate:
        case eFMS_Complete:
        case eFMS_Failed:
        case eFMS_Resetting:
            nMissionState = eFMS_Ready;
            break;
        case eFMS_Blocked:
            nMissionState = eFMS_Blocked;
            break;
        }
    }

    bool cFinalMission::ArePrerequisitesComplete() const
    {
        return m_eMissionState != eFMS_Blocked;
    }
}
