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
#include "cd2/memory.h"
#include "lua/lua.h"
#include <new>

namespace AI
{
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
