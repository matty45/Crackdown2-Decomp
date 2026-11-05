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

// Not named yet: GetBool38_50 (0x823EC378) is an unnamed boolean accessor; m_p50 (0x50) is untyped storage.

#include "fun_runtime/script_type_registrar.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacterInterface.h"
#include "AI/cCharacterEntityIF.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>

namespace AI
{
    bool cCharacterEntityIF::IsInViewCone(Fun_Runtime::cScriptHost *object)
    {
        return m_pAIEntity->IsInViewCone(object);
    }
}

Fun_Runtime::cScriptTypeRegistrar<AI::cCharacterEntityIF> g_cCharacterEntityIF("cCharacterEntityIF", "cCharacterInterface");     // global at 0x838035CC
unsigned char g_AIE_OBJECT_APPROACHING;     // global at 0x8381764C
unsigned char g_AIE_EJECTED_FROM_VEHICLE;     // global at 0x83817728
unsigned char g_AIE_TARGETED;     // global at 0x83817770
unsigned char g_AIE_INTERESTING_OBJECT;     // global at 0x83817890
unsigned char g_AIE_INTERESTING_OBJECT_BASIC_REACTION;     // global at 0x838178B4
unsigned char g_AIE_DAMAGE_TAKEN;     // global at 0x83818CE0
unsigned char g_AIE_DIED;     // global at 0x83818D04
unsigned char g_AIE_EQUIPMENT_LOST;     // global at 0x83818D94
unsigned char g_AIE_CARRIED_OBJECT_LOST;     // global at 0x83818DB8
unsigned char g_AIE_SET_ON_FIRE;     // global at 0x83818E00
unsigned char g_AIE_END_FIRE;     // global at 0x83818E24
unsigned char g_AIE_TOUCHED;     // global at 0x83818940
unsigned char g_AIE_TOUCHED_GRENADE;     // global at 0x83818964

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

    void *cCharacterEntityIF::RetUpperbodyAnimationParams()
    {
        return m_upperbodyAnimationParams;
    }

    void *cCharacterEntityIF::RetFullbodyAnimationParams()
    {
        return m_fullbodyAnimationParams;
    }

    void *cCharacterEntityIF::GetPtrcCharacterEntityIF() const
    {
        return &g_cCharacterEntityIF;
    }

    void *cCharacterEntityIF::GetPtrAIE_OBJECT_APPROACHING() const
    {
        return &g_AIE_OBJECT_APPROACHING;
    }

    void *cCharacterEntityIF::GetPtrAIE_EJECTED_FROM_VEHICLE() const
    {
        return &g_AIE_EJECTED_FROM_VEHICLE;
    }

    void *cCharacterEntityIF::GetPtrAIE_TARGETED() const
    {
        return &g_AIE_TARGETED;
    }

    void *cCharacterEntityIF::GetPtrAIE_INTERESTING_OBJECT() const
    {
        return &g_AIE_INTERESTING_OBJECT;
    }

    void *cCharacterEntityIF::GetPtrAIE_INTERESTING_OBJECT_BASIC_REACTION() const
    {
        return &g_AIE_INTERESTING_OBJECT_BASIC_REACTION;
    }

    void *cCharacterEntityIF::GetPtrAIE_DAMAGE_TAKEN() const
    {
        return &g_AIE_DAMAGE_TAKEN;
    }

    void *cCharacterEntityIF::GetPtrAIE_DIED() const
    {
        return &g_AIE_DIED;
    }

    void *cCharacterEntityIF::GetPtrAIE_EQUIPMENT_LOST() const
    {
        return &g_AIE_EQUIPMENT_LOST;
    }

    void *cCharacterEntityIF::GetPtrAIE_CARRIED_OBJECT_LOST() const
    {
        return &g_AIE_CARRIED_OBJECT_LOST;
    }

    void *cCharacterEntityIF::GetPtrAIE_SET_ON_FIRE() const
    {
        return &g_AIE_SET_ON_FIRE;
    }

    void *cCharacterEntityIF::GetPtrAIE_END_FIRE() const
    {
        return &g_AIE_END_FIRE;
    }

    void *cCharacterEntityIF::GetPtrAIE_TOUCHED() const
    {
        return &g_AIE_TOUCHED;
    }

    void *cCharacterEntityIF::GetPtrAIE_TOUCHED_GRENADE() const
    {
        return &g_AIE_TOUCHED_GRENADE;
    }

    unsigned char cCharacterEntityIF::RetMovementType() const
    {
        return static_cast<unsigned char>(m_nMovementType);
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

    const char *cCharacterEntityIF::RetMovementTypeEnum() const
    {
        return "eMovementType";
    }

    const char *cCharacterEntityIF::RetPerceptionOptions() const
    {
        return "ePerceptionOptions";
    }

    const char *cCharacterEntityIF::RetFaceTarget() const
    {
        return "eFaceTarget";
    }

    const char *cCharacterEntityIF::RetAttackState() const
    {
        return "eAttackState";
    }

    const char *cCharacterEntityIF::RetState() const
    {
        return "eState";
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

    unsigned char cCharacterEntityIF::GetBool38_50() const
    {
        bool result = (unsigned int)(&m_eNetRole)[-1] != 0 &&
            m_p50 != 0;
        return result;
    }

    unsigned char cCharacterEntityIF::IsSpawnedByCrowdSystem() const
    {
        const CHARACTER::cCharacter *character = RetCharacter();
        if (character)
        {
            const unsigned int v = character->m_field548;
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
        if ((p->m_byte1681 & 0x40) != 0)
            return 180.0f;
        return t->m_fViewingAngle;
    }

    static RWS::CClassFactory::CRegistrar cCharacterEntityIFRegistrar(
        "cCharacterEntityIF", cCharacterEntityIF::MakeNew, 0x540, false);

    // CD2 0x82F60D58: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCharacterEntityIFcCharacterInterfaceInheritRegistrar(
        AI::cCharacterEntityIF::StaticCreateClass(), CHARACTER::cCharacterInterface::StaticCreateClass());

    // CD2 0x82F60E10: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCharacterEntityIFSpawningRegistrar(
        cCharacterEntityIF::StaticCreateClass(), cCharacterEntityIF::SpawnFromPrototype);
}
