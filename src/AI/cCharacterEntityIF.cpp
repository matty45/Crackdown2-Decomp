// src/AI/cCharacterEntityIF.cpp
//
// Class: cCharacterEntityIF (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCharacterEntityIF.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/cCharacterEntityIF.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/cCharacterEntityIF.cpp

// Open: 0x823EC378, a boolean accessor, is slot 7 of nine vtables whose class is not modelled.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/script_type_registrar.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacterInterface.h"
#include "AI/cCharacterEntityIF.h"
#include "AI/cStoreItemAgent.h"
#include "AI/cIdleAgent.h"
#include "AI/cReloadAgent.h"
#include "AI/cPrimaryFireAgent.h"
#include "AI/cSecondaryFireAgent.h"
#include "AI/cThrowAgent.h"
#include "AI/cUpperBodyAnimateAndFaceAgent.h"
#include "AI/cPickUpItemAgent.h"
#include "AI/cPickUpAgent.h"
#include "AI/cDropAgent.h"
#include "AI/cCrouchAgent.h"
#include "AI/cUncrouchAgent.h"
#include "AI/cExitVehicleAgent.h"
#include "AI/cChaseAndReloadAgent.h"
#include "AI/cInterceptAgent.h"
#include "AI/cMoveAgent.h"
#include "AI/cMoveAndFaceAgent.h"
#include "AI/cMoveAndPrimaryFireAgent.h"
#include "AI/cBackAwayAgent.h"
#include "AI/cDodgeAgent.h"
#include "AI/cMoveAndReloadAgent.h"
#include "AI/cUpperBodyAnimateAndMoveAgent.h"
#include "AI/cChaseAndPrimaryFireAgent.h"
#include "AI/cFaceAndPrimaryFireAgent.h"
#include "AI/cIntelliFleeAgent.h"
#include "AI/cWanderFleeAgent.h"
#include "AI/cFollowAgent.h"
#include "AI/cBrakeAgent.h"
#include "AI/cProtectAgent.h"
#include "AI/cReactionAgent.h"
#include "AI/cSafeDistancePrimaryFireAgent.h"
#include "AI/cSimpleDrivingAvoidanceAgent.h"
#include "AI/cCircleAgent.h"
#include "AI/cCloseAttackAgent.h"
#include "AI/cObjectInstigatorEvent.h"
#include "AI/cDamageTakenEvent.h"
#include "AI/cDiedEvent.h"
#include "AI/cTouchedGrenadeEvent.h"
#include "AI/cTouchedEvent.h"
#include "AI/cInterestingObjectBasicReactionEvent.h"
#include "AI/cInterestingObjectEvent.h"
#include "AI/cTargetedEvent.h"
#include "AI/cEjectedFromVehicleEvent.h"
#include "AI/cSetOnFireEvent.h"
#include "AI/cEndFireEvent.h"
#include "AI/cCarriedObjectLostEvent.h"
#include "AI/cEquipmentLostEvent.h"
#include "AI/cMovementTypeScriptRegistration.h"
#include "AI/cPerceptionOptionsScriptRegistration.h"
#include "AI/cStateScriptRegistration.h"
#include "AI/cAttackStateScriptRegistration.h"
#include "AI/cFaceTargetScriptRegistration.h"
#include "rws/classfactory.h"
#include "fun_runtime/retval.h"
#include "cd2/memory.h"
#include "lua/lua.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass &cCharacterEntityIF::RetClass() const
    {
        return *ms_pcCharacterEntityIFClass;
    }

    bool cCharacterEntityIF::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcCharacterEntityIFClass->IsA(c);
    }

    bool cCharacterEntityIF::IsInViewCone(Fun_Runtime::cScriptHost *object)
    {
        return m_pAIEntity->IsInViewCone(object);
    }
}

Fun_Runtime::cScriptTypeRegistrar<AI::cCharacterEntityIF> g_cCharacterEntityIF("cCharacterEntityIF", "cCharacterInterface");     // global at 0x838035CC

namespace AI
{
    // CD2 0x82F60D30 initializes the descriptor at 0x838035C0 through StaticCreateClass.
    const Fun_Runtime::cClass *cCharacterEntityIF::ms_pcCharacterEntityIFClass =
        &cCharacterEntityIF::StaticCreateClass();

    Fun_Runtime::cClass &cCharacterEntityIF::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCharacterEntityIFClass =
            new Fun_Runtime::cClass(0x5F1, "cCharacterEntityIF", 0x540);
        return *cCharacterEntityIFClass;
    }

    RWS::CAttributeHandler *cCharacterEntityIF::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCharacterEntityIFPrototype(packet);
    }

    RWS::CAttributeHandler *cCharacterEntityIF::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCharacterEntityIF;
        return 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cCharacterEntityIF::RetScriptTypeRegistration() const
    {
        return &g_cCharacterEntityIF;
    }

    const char *cMovementTypeScriptRegistration::RetName() const
    {
        return "eMovementType";
    }

    const char *cPerceptionOptionsScriptRegistration::RetName() const
    {
        return "ePerceptionOptions";
    }

    const char *cFaceTargetScriptRegistration::RetName() const
    {
        return "eFaceTarget";
    }

    const char *cAttackStateScriptRegistration::RetName() const
    {
        return "eAttackState";
    }

    const char *cStateScriptRegistration::RetName() const
    {
        return "eState";
    }

    void *cCharacterEntityIF::RetUpperbodyAnimationParams()
    {
        return m_upperbodyAnimationParams;
    }

    void *cCharacterEntityIF::RetFullbodyAnimationParams()
    {
        return m_fullbodyAnimationParams;
    }

    unsigned char cCharacterEntityIF::RetMovementType() const
    {
        return static_cast<unsigned char>(m_nMovementType);
    }

    unsigned int cCharacterEntityIF::RetCharacterState()
    {
        return RetCharacter()->RetCharacterState();
    }

    Equip::cEquipment *cCharacterEntityIF::AddEquipment(const char *sProtoName)
    {
        return cCharacterInterface::AddEquipment(sProtoName, true, false, 0, false);
    }

    Equip::cEquipment *cCharacterEntityIF::AddEquipmentDontEquip(const char *sProtoName)
    {
        return cCharacterInterface::AddEquipment(sProtoName, false, false, 0, false);
    }

    unsigned int cCharacterEntityIF::RetMaxAiToAiVisibilityLevel() const
    {
        return m_nMaxAiToAiVisibilityLevel;
    }

    void cCharacterEntityIF::SetMaxAiToAiVisibilityLevel(unsigned int value)
    {
        m_nMaxAiToAiVisibilityLevel = value;
    }

    void cCharacterEntityIF::SetCheckTargetTooClose(unsigned char value)
    {
        m_bCheckingTargetTooClose = value;
    }

    void cCharacterEntityIF::SetCheckTargetAreaClear(unsigned char value)
    {
        m_bCheckingTargetAreaClear = value;
    }

    void cCharacterEntityIF::SetCheckTargetPathClear(unsigned char value)
    {
        m_bCheckingTargetPathClear = value;
    }

    void cCharacterEntityIF::SetCheckTargetBlocked(unsigned char value)
    {
        m_bCheckingTargetBlocked = value;
    }

    unsigned char cCharacterEntityIF::IsCheckingTargetTooClose() const
    {
        return m_bCheckingTargetTooClose;
    }

    unsigned char cCharacterEntityIF::IsCheckingTargetAreaClear() const
    {
        return m_bCheckingTargetAreaClear;
    }

    unsigned char cCharacterEntityIF::IsCheckingTargetPathClear() const
    {
        return m_bCheckingTargetPathClear;
    }

    unsigned char cCharacterEntityIF::IsCheckingTargetBlocked() const
    {
        return m_bCheckingTargetBlocked;
    }

    void cCharacterEntityIF::SetBulletSoundLODDeafnessEnabled(unsigned char value)
    {
        m_bBulletSoundLODDeafnessEnabled = value;
    }

    const char *cCharacterEntityIF::RetClassName() const
    {
        return "cCharacterEntityIF";
    }

    void *cCharacterEntityIF::RetHeadDirection() const
    {
        return &m_pAIEntity->m_vecHeadDirection;
    }

    void *cCharacterEntityIF::RetEyePosition() const
    {
        return &m_pAIEntity->m_vecEyePosition;
    }

    float cCharacterEntityIF::RetViewingDistance() const
    {
        return m_pAIEntity->m_fViewingDistance;
    }

    float cCharacterEntityIF::RetThreatObjectViewingDistance() const
    {
        return m_pAIEntity->m_fThreatObjectViewingDistance;
    }

    float cCharacterEntityIF::RetHearingAcuteness() const
    {
        return m_pAIEntity->m_fHearingAcuteness;
    }

    unsigned char cCharacterEntityIF::IsSpawnedByCrowdSystem() const
    {
        const CHARACTER::cCharacter *character = RetCharacter();
        if (character)
        {
            const unsigned int v = character->m_nObjectID;
            return (0x30000 - (v & 0xFFFF0000)) == 0;
        }
        return 0;
    }

    float cCharacterEntityIF::RetViewingAngle() const
    {
        cCharacterEntity *t = m_pAIEntity;
        cCharacterEntityIF *owner = t->m_pOwner;
        Fun_Runtime::cSafeDeletable *safe = owner->m_pCharacter.m_pPtr;
        const CHARACTER::cCharacter *p = static_cast<const CHARACTER::cCharacter *>(safe);
        if ((p->RetActionManager().RetCharacterStateInfo().m_flags[1] & 0x40) != 0)
            return 180.0f;
        return t->m_fViewingAngle;
    }

    void cCharacterEntityIF::vf105()
    {
        cSimpleDrivingAvoidanceAgent *pAgent = m_pCharacterBrain->CreateAgent<cSimpleDrivingAvoidanceAgent>();
        if (m_pCharacterBrain->RetActiveAgent() == pAgent)
            pAgent->VehicleEnterPhysicalState();
    }

    void cCharacterEntityIF::vf106()
    {
        cSimpleDrivingAvoidanceAgent *pAgent = m_pCharacterBrain->CreateAgent<cSimpleDrivingAvoidanceAgent>();
        if (m_pCharacterBrain->RetActiveAgent() == pAgent)
            pAgent->VehicleLeavePhysicalState();
    }

    void cCharacterEntityIF::SetGameImportance(eGameImportance nGI)
    {
        RetCharacter()->SetGameImportance(nGI);
        cCharacterInterface::SetGameImportance(nGI);
    }

    float cCharacterEntityIF::RetHeight()
    {
        return m_pAIEntity->m_attrHeight->GetHeight();
    }

    float cCharacterEntityIF::RetRadius()
    {
        return m_pAIEntity->m_attrWidth->GetWidth() * 0.5f;
    }

    void cCharacterEntityIF::SetPerceptionOptions(unsigned int nPerceptionOptions)
    {
        m_nPerceptionOptions = nPerceptionOptions;
    }

    void cCharacterEntityIF::SetViewingAngle(float fViewingAngle)
    {
        m_pAIEntity->SetViewingAngle(fViewingAngle);
    }

    void cCharacterEntityIF::SetViewingDistance(float fViewingDistance)
    {
        m_pAIEntity->m_fViewingDistance = fViewingDistance;
    }

    void cCharacterEntityIF::SetPlayerViewingDistance(float fViewingDistance)
    {
        m_pAIEntity->m_fPlayerViewingDistance = fViewingDistance;
    }

    void cCharacterEntityIF::SetThreatObjectViewingDistance(float fViewingDistance)
    {
        m_pAIEntity->m_fThreatObjectViewingDistance = fViewingDistance;
    }

    void cCharacterEntityIF::SetHearingAcuteness(float fHearingAcuteness)
    {
        m_pAIEntity->m_fHearingAcuteness = fHearingAcuteness;
    }

    bool cCharacterEntityIF::IsVisible(cGameBase *object)
    {
        float visibilityDate;
        return IsVisible(object, visibilityDate);
    }

    void cCharacterEntityIF::Idle()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cIdleAgent>());
    }

    void cCharacterEntityIF::Reload(float fTolerance)
    {
        cReloadAgent *pAgent = m_pCharacterBrain->CreateAgent<cReloadAgent>();
        pAgent->SetTolerance(fTolerance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::MoveTo(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout,
        float fAcceptableDistance)
    {
        cMoveAgent *pAgent = m_pCharacterBrain->CreateAgent<cMoveAgent>();
        Fun_Runtime::Vec3 vecDestination;
        vecDestination.Set(vecPos.x, vecPos.y, vecPos.z);
        pAgent->SetDestination(vecDestination, true, false);
        pAgent->SetStuckTimeout(fStuckTimeout);
        pAgent->SetUsePrecision(bUsePrecision);
        pAgent->SetAcceptableReachedDestinationDistance(fAcceptableDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::MoveAndFace(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout,
        float fAcceptableDistance)
    {
        cMoveAndFaceAgent *pAgent = m_pCharacterBrain->CreateAgent<cMoveAndFaceAgent>();
        Fun_Runtime::Vec3 vecDestination;
        vecDestination.Set(vecPos.x, vecPos.y, vecPos.z);
        pAgent->SetDestination(vecDestination, true, false);
        pAgent->SetStuckTimeout(fStuckTimeout);
        pAgent->SetUsePrecision(bUsePrecision);
        pAgent->SetAcceptableReachedDestinationDistance(fAcceptableDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::MoveAndReload(Fun_Runtime::OldVec3 vecPos, bool bUsePrecision, float fStuckTimeout,
        float fAcceptableDistance)
    {
        cMoveAndReloadAgent *pAgent = m_pCharacterBrain->CreateAgent<cMoveAndReloadAgent>();
        Fun_Runtime::Vec3 vecDestination;
        vecDestination.Set(vecPos.x, vecPos.y, vecPos.z);
        pAgent->SetDestination(vecDestination, true, false);
        pAgent->SetStuckTimeout(fStuckTimeout);
        pAgent->SetUsePrecision(bUsePrecision);
        pAgent->SetAcceptableReachedDestinationDistance(fAcceptableDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::MoveAndPrimaryFire(Fun_Runtime::OldVec3 vecPos, float fSuppressingFireTime,
        bool bFaceTargetWhenNotFiring, bool bUsePrecision, float fStuckTimeout, float fAcceptableDistance)
    {
        cMoveAndPrimaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cMoveAndPrimaryFireAgent>();
        Fun_Runtime::Vec3 vecDestination;
        vecDestination.Set(vecPos.x, vecPos.y, vecPos.z);
        pAgent->SetDestination(vecDestination, true, false);
        pAgent->SetSurpressingFireTime(fSuppressingFireTime);
        pAgent->SetFaceTargetWhenNotFiring(bFaceTargetWhenNotFiring);
        pAgent->SetStuckTimeout(fStuckTimeout);
        pAgent->SetUsePrecision(bUsePrecision);
        pAgent->SetAcceptableReachedDestinationDistance(fAcceptableDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Follow(float fMinDistance, float fMaxDistance)
    {
        cFollowAgent *pAgent = m_pCharacterBrain->CreateAgent<cFollowAgent>();
        pAgent->SetDistances(fMinDistance, fMaxDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::ResetIntelliFleeTimeout()
    {
        m_pCharacterBrain->CreateAgent<cIntelliFleeAgent>()->ResetTimeout();
    }

    void cCharacterEntityIF::SetIntelliFleeUpperBodyAnim(bool bUse, int nAnimID)
    {
        m_pCharacterBrain->CreateAgent<cIntelliFleeAgent>()->SetUpperBodyAnim(bUse, nAnimID);
    }

    void cCharacterEntityIF::SetIntelliFleeLookBehindAnim(bool bUse, int nLookAnimID, int nTurnAnimID, float fMinTime,
        float fMaxTime)
    {
        m_pCharacterBrain->CreateAgent<cIntelliFleeAgent>()->SetLookBehindAnim(bUse, nLookAnimID, nTurnAnimID, fMinTime,
            fMaxTime);
    }

    void cCharacterEntityIF::SetIntelliFleeCowerAnim(int nStartAnimID, int nLoopAnimID, int nEndAnimID)
    {
        m_pCharacterBrain->CreateAgent<cIntelliFleeAgent>()->SetCowerAnims(nStartAnimID, nLoopAnimID, nEndAnimID);
    }

    void cCharacterEntityIF::SetIntelliFleePanicAnim(int nAnimID)
    {
        m_pCharacterBrain->CreateAgent<cIntelliFleeAgent>()->SetPanicAnim(nAnimID);
    }

    void cCharacterEntityIF::SetWanderFleeAvoidPosition(const Fun_Runtime::OldVec3 &vPosition)
    {
        m_pCharacterBrain->CreateAgent<cWanderFleeAgent>()->SetAvoidPosition(vPosition);
    }

    void cCharacterEntityIF::SetWanderFleeAvoidObject(cGameBase *pObject)
    {
        m_pCharacterBrain->CreateAgent<cWanderFleeAgent>()->SetAvoidObject(pObject);
    }

    void cCharacterEntityIF::SetWanderFleeUpperBodyAnim(bool bUse, int nAnimID)
    {
        m_pCharacterBrain->CreateAgent<cWanderFleeAgent>()->SetUpperBodyAnim(bUse, nAnimID);
    }

    void cCharacterEntityIF::SetWanderFleeLookBehindAnim(bool bUse, int nLookAnimID, int nTurnAnimID, float fMinTime,
        float fMaxTime)
    {
        m_pCharacterBrain->CreateAgent<cWanderFleeAgent>()->SetLookBehindAnim(bUse, nLookAnimID, nTurnAnimID, fMinTime,
            fMaxTime);
    }

    void cCharacterEntityIF::FaceAndPrimaryFire(float fSuppressingFireTime, float fTolerance, float fFirePauseTime,
        float fMinTargetDistance, float fMaxTargetDistance)
    {
        cFaceAndPrimaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cFaceAndPrimaryFireAgent>();
        pAgent->SetSurpressingFireTime(fSuppressingFireTime);
        pAgent->SetTolerance(fTolerance);
        pAgent->SetFirePauseTime(fFirePauseTime);
        pAgent->SetEnemyDistances(fMinTargetDistance, fMaxTargetDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Reaction(const Fun_Runtime::Vec3 &vReactionPos, char nReaction, unsigned int nReactionFlags,
        float fReactionChance, Fun_Runtime::Vec3 *pReactionSourceVelo)
    {
        cReactionAgent *pAgent = m_pCharacterBrain->CreateAgent<cReactionAgent>();
        if (pReactionSourceVelo)
            pAgent->SetReactionSourceVelocity(*pReactionSourceVelo);
        pAgent->SetReactionPos(vReactionPos);
        pAgent->SetReaction(nReaction);
        pAgent->SetReactionFlags(nReactionFlags);
        SetActiveAgent(pAgent);
        pAgent->SetReactionChance(fReactionChance);
    }

    void cCharacterEntityIF::SafeDistancePrimaryFire(float fDistance, float fFirePauseTime, bool bFiringEnabled,
        bool bFaceTargetWhenNotFiring)
    {
        cSafeDistancePrimaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cSafeDistancePrimaryFireAgent>();
        pAgent->SetFirePauseTime(fFirePauseTime);
        pAgent->SetDistance(fDistance);
        pAgent->SetFiringEnabled(bFiringEnabled);
        pAgent->SetFaceTargetWhenNotFiring(bFaceTargetWhenNotFiring);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::PrimaryFire(float fTolerance)
    {
        cPrimaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cPrimaryFireAgent>();
        pAgent->SetTolerance(fTolerance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::SecondaryFire(float fTolerance)
    {
        cSecondaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cSecondaryFireAgent>();
        pAgent->SetTolerance(fTolerance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Throw(float fTolerance)
    {
        cThrowAgent *pAgent = m_pCharacterBrain->CreateAgent<cThrowAgent>();
        pAgent->SetTolerance(fTolerance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::UpperBodyAnimateAndFace()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cUpperBodyAnimateAndFaceAgent>());
    }

    void cCharacterEntityIF::UpperBodyAnimateAndMove(Fun_Runtime::OldVec3 vecPos)
    {
        cUpperBodyAnimateAndMoveAgent *pAgent = m_pCharacterBrain->CreateAgent<cUpperBodyAnimateAndMoveAgent>();
        Fun_Runtime::Vec3 vecDestination;
        vecDestination.Set(vecPos.x, vecPos.y, vecPos.z);
        pAgent->SetDestination(vecDestination, true, false);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::SetCharacterStateProfileFromID(unsigned int profile)
    {
        RetCharacter()->SetCharacterStateProfileFromIndex(profile);
    }

    void cCharacterEntityIF::StoreItem()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cStoreItemAgent>());
    }

    void cCharacterEntityIF::PickUpItem()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cPickUpItemAgent>());
    }

    void cCharacterEntityIF::PickUp()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cPickUpAgent>());
    }

    void cCharacterEntityIF::Drop()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cDropAgent>());
    }

    void cCharacterEntityIF::Crouch()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cCrouchAgent>());
    }

    void cCharacterEntityIF::Uncrouch()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cUncrouchAgent>());
    }

    void cCharacterEntityIF::ExitVehicle()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cExitVehicleAgent>());
    }

    void cCharacterEntityIF::CloseAttack(float fTime)
    {
        cCloseAttackAgent *pAgent = m_pCharacterBrain->CreateAgent<cCloseAttackAgent>();
        pAgent->SetCloseAttackTime(fTime);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::ProtectPosition(float fRadius, Fun_Runtime::OldVec3 vPosition, float fSuppressingFireTime)
    {
        cProtectAgent *pAgent = m_pCharacterBrain->CreateAgent<cProtectAgent>();
        Fun_Runtime::Vec3 vecPosition;
        vecPosition.Set(vPosition.x, vPosition.y, vPosition.z);
        pAgent->SetProtectRadius(fRadius);
        pAgent->SetProtectPosition(vecPosition);
        pAgent->SetSurpressingFireTime(fSuppressingFireTime);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::ProtectObject(float fRadius, cGameBase *pObject, float fSuppressingFireTime)
    {
        cProtectAgent *pAgent = m_pCharacterBrain->CreateAgent<cProtectAgent>();
        pAgent->SetProtectRadius(fRadius);
        pAgent->SetProtectObject(pObject);
        pAgent->SetSurpressingFireTime(fSuppressingFireTime);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Circle(float fDistance, bool bAdjustMovement, bool bLockDirection, float fTimeout)
    {
        cCircleAgent *pAgent = m_pCharacterBrain->CreateAgent<cCircleAgent>();
        pAgent->SetDistance(fDistance);
        pAgent->SetAdjustMovement(bAdjustMovement);
        pAgent->SetStuckTimeout(fTimeout);
        pAgent->SetDirectionLocked(bLockDirection);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::BackAway(bool bAdjustMovement, float fSafeDistance, float fTooCloseDistance)
    {
        cBackAwayAgent *pAgent = m_pCharacterBrain->CreateAgent<cBackAwayAgent>();
        pAgent->SetAdjustMovement(bAdjustMovement);
        pAgent->SetSafeDistance(fSafeDistance);
        pAgent->SetTargetTooCloseDistance(fTooCloseDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Dodge(bool bFiringEnabled, bool bFaceTargetWhenNotFiring)
    {
        cDodgeAgent *pAgent = m_pCharacterBrain->CreateAgent<cDodgeAgent>();
        pAgent->SetFiringEnabled(bFiringEnabled);
        pAgent->SetFaceTargetWhenNotFiring(bFaceTargetWhenNotFiring);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Brake(bool bBrakeFlag, float fStopSpeed)
    {
        cBrakeAgent *pAgent = m_pCharacterBrain->CreateAgent<cBrakeAgent>();
        pAgent->SetBrake(bBrakeFlag, fStopSpeed);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Face(float fTolerance)
    {
        cFaceAgent *pAgent = m_pCharacterBrain->CreateAgent<cFaceAgent>();
        pAgent->SetTolerance(fTolerance);
        pAgent->SetFaceTarget();
        pAgent->SetTargetFacingEnabled(true);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::Face(float fTolerance, const Fun_Runtime::OldVec3 &vPointToFace)
    {
        cFaceAgent *pAgent = m_pCharacterBrain->CreateAgent<cFaceAgent>();
        pAgent->SetTolerance(fTolerance);
        pAgent->SetFacePoint(vPointToFace);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::SetBreakTrafficLaws(unsigned char value)
    {
        m_bBreakTrafficLaws = value;
    }

    void cCharacterEntityIF::Chase(bool bUseDefendedPosition, cGameBase *pDefendedObject,
        Fun_Runtime::OldVec3 vecDefendedPosition, float fRadius)
    {
        cChaseAgent *pAgent = m_pCharacterBrain->CreateAgent<cChaseAgent>();
        Fun_Runtime::Vec3 vecPosition;
        vecPosition.Set(vecDefendedPosition.x, vecDefendedPosition.y, vecDefendedPosition.z);
        pAgent->SetDefendedPosition(bUseDefendedPosition, pDefendedObject, vecPosition, fRadius);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::ChaseAndPrimaryFire(float fSuppressingFireTime, bool bFaceTargetWhenNotFiring,
        float fAcceptableDistance, float fTargetTooFarDistance, Fun_Runtime::Vec3 vGuardPoint, float fGuardDistance)
    {
        cChaseAndPrimaryFireAgent *pAgent = m_pCharacterBrain->CreateAgent<cChaseAndPrimaryFireAgent>();
        pAgent->SetSurpressingFireTime(fSuppressingFireTime);
        pAgent->SetFaceTargetWhenNotFiring(bFaceTargetWhenNotFiring);
        pAgent->SetAcceptableReachedDestinationDistance(fAcceptableDistance);
        pAgent->SetTargetTooFarDistance(fTargetTooFarDistance);
        pAgent->SetGuardPointAndDistance(vGuardPoint, fGuardDistance);
        SetActiveAgent(pAgent);
    }

    void cCharacterEntityIF::ChaseAndReload()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cChaseAndReloadAgent>());
    }

    void cCharacterEntityIF::Intercept()
    {
        SetActiveAgent(m_pCharacterBrain->CreateAgent<cInterceptAgent>());
    }

    bool cCharacterEntityIF::ForceIntoVehicle(Vehicle::cVehicle *pVehicle, unsigned int nSeat)
    {
        m_pCharacterBrain->SetInVehicle(true);
        return cCharacterInterface::ForceIntoVehicle(pVehicle, nSeat);
    }

    bool cCharacterEntityIF::ForceOutOfVehicle()
    {
        m_pCharacterBrain->SetInVehicle(false);
        return RetCharacter()->RetActionManager().ForceOutOfVehicle();
    }

    void cCharacterEntityIF::DropImmediately()
    {
        m_pCharacterBrain->DropImmediately();
    }

    void cCharacterEntityIF::ExitVehicleImmediately()
    {
        m_pCharacterBrain->SetInVehicle(false);
    }

    void cCharacterEntityIF::CrouchImmediately()
    {
        m_pCharacterBrain->CrouchImmediately();
    }

    void cCharacterEntityIF::UncrouchImmediately()
    {
        m_pCharacterBrain->UncrouchImmediately();
    }

    bool cCharacterEntityIF::IsTryingToCrouch()
    {
        return m_pCharacterBrain->IsTryingToCrouch();
    }

    void cCharacterEntityIF::SetAiming(bool bAiming)
    {
        m_pCharacterBrain->SetAiming(bAiming);
    }

    void cCharacterEntityIF::SetActiveAgent(cAgent *pState)
    {
        m_pCharacterBrain->SetActiveAgent(pState);
    }

    void cCharacterEntityIF::ClearBrainState()
    {
        m_pCharacterBrain->ClearActiveAgent();
    }

    bool cCharacterEntityIF::IsAIEntityOwner(Kaim::CEntity *pEntity)
    {
        return pEntity == m_pAIEntity;
    }

    void cCharacterEntityIF::ClearRooftopPoint(bool bClear)
    {
        m_bRooftopPointSet = false;
        if (bClear)
            m_pRooftopPoint = 0;
    }

    void *cCharacterEntityIF::RetRooftopPoint()
    {
        return m_pRooftopPoint;
    }

    Fun_Runtime::RetVal cCharacterEntityIF::cCharacterEntityIFPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    cObjectInstigatorEvent::cObjectInstigatorEvent(Fun_Runtime::cScriptHost *source,
        cCharacterEntityIF *instigator, cNonGameBase *object)
        : cAIEvent(0x6B, source), m_pObject(object), m_pInstigator(instigator)
    {
    }

    const Fun_Runtime::cScriptTypeRegistration *cObjectInstigatorEvent::RetScriptTypeRegistration() const
    {
        return &g_cObjectApproachingEvent;
    }

    bool cObjectInstigatorEvent::IsValid()
    {
        return cAIEvent::IsValid() && m_pObject != 0;
    }

    const Fun_Runtime::cScriptTypeRegistration *cEjectedFromVehicleEvent::RetScriptTypeRegistration() const
    {
        return &g_cEjectedFromVehicleEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cTargetedEvent::RetScriptTypeRegistration() const
    {
        return &g_cTargetedEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cInterestingObjectEvent::RetScriptTypeRegistration() const
    {
        return &g_cInterestingObjectEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cInterestingObjectBasicReactionEvent::RetScriptTypeRegistration() const
    {
        return &g_cInterestingObjectBasicReactionEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDamageTakenEvent::RetScriptTypeRegistration() const
    {
        return &g_cDamageTakenEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cDiedEvent::RetScriptTypeRegistration() const
    {
        return &g_cDiedEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cEquipmentLostEvent::RetScriptTypeRegistration() const
    {
        return &g_cEquipmentLostEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cCarriedObjectLostEvent::RetScriptTypeRegistration() const
    {
        return &g_cCarriedObjectLostEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cSetOnFireEvent::RetScriptTypeRegistration() const
    {
        return &g_cSetOnFireEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cEndFireEvent::RetScriptTypeRegistration() const
    {
        return &g_cEndFireEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cTouchedEvent::RetScriptTypeRegistration() const
    {
        return &g_cTouchedEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cTouchedGrenadeEvent::RetScriptTypeRegistration() const
    {
        return &g_cTouchedGrenadeEvent;
    }

    void cStateScriptRegistration::RegisterValues(lua_State *state)
    {
        lua_pushliteral(state, "nNone");
        lua_pushnumber(state, 0.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "nWander");
        lua_pushnumber(state, 1.0f);
        lua_settable(state, -3);
        lua_pushliteral(state, "nRetreat");
        lua_pushnumber(state, 2.0f);
        lua_settable(state, -3);
    }

    static RWS::CClassFactory::CRegistrar cCharacterEntityIFRegistrar(
        "cCharacterEntityIF", cCharacterEntityIF::MakeNew, 0x540, false);

    // CD2 0x82F60D58: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCharacterEntityIFcCharacterInterfaceInheritRegistrar(
        AI::cCharacterEntityIF::StaticCreateClass(), CHARACTER::cCharacterInterface::StaticCreateClass());

    // CD2 0x82F60E10: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCharacterEntityIFSpawningRegistrar(
        cCharacterEntityIF::StaticCreateClass(), cCharacterEntityIF::SpawnFromPrototype);
    // CD2 0x82F60EB0 registers this four-byte enum object at 0x838035F0.
    static cMovementTypeScriptRegistration g_cMovementTypeScriptRegistration;

    // CD2 0x82F60EF8 registers the perception enum at 0x838035F4.
    static cPerceptionOptionsScriptRegistration g_cPerceptionOptionsScriptRegistration;

    // CD2 0x82F60F40 registers the facing enum at 0x838035F8.
    static cFaceTargetScriptRegistration g_cFaceTargetScriptRegistration;

    // CD2 0x82F60F88 registers the behavior-state enum at 0x838035FC.
    static cStateScriptRegistration g_cStateScriptRegistration;

    // CD2 0x82F60FD0 registers the attack-state enum at 0x83803600.
    static cAttackStateScriptRegistration g_cAttackStateScriptRegistration;

}
