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

#include "AI/cCharacterEntityIF.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

inline void *operator new(size_t, void *memory) { return memory; }

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

    RWS::CAttributeHandler *cCharacterEntityIF::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCharacterEntityIF;
        return 0;
    }

    void *cCharacterEntityIF::GetStorage480()
    {
        return m_storage480;
    }

    void *cCharacterEntityIF::GetStorage4B0()
    {
        return m_storage4B0;
    }

    unsigned char cCharacterEntityIF::GetWord50CLowByte() const
    {
        return static_cast<unsigned char>(m_word50C);
    }

    unsigned int cCharacterEntityIF::GetWord51C() const
    {
        return m_word51C;
    }

    void cCharacterEntityIF::SetWord51C(unsigned int value)
    {
        m_word51C = value;
    }

    void cCharacterEntityIF::SetByte534(unsigned char value)
    {
        m_byte534 = value;
    }

    void cCharacterEntityIF::SetByte535(unsigned char value)
    {
        m_byte535 = value;
    }

    void cCharacterEntityIF::SetByte536(unsigned char value)
    {
        m_byte536 = value;
    }

    void cCharacterEntityIF::SetByte537(unsigned char value)
    {
        m_byte537 = value;
    }

    unsigned char cCharacterEntityIF::GetByte534() const
    {
        return m_byte534;
    }

    unsigned char cCharacterEntityIF::GetByte535() const
    {
        return m_byte535;
    }

    unsigned char cCharacterEntityIF::GetByte536() const
    {
        return m_byte536;
    }

    unsigned char cCharacterEntityIF::GetByte537() const
    {
        return m_byte537;
    }

    void cCharacterEntityIF::SetByte539(unsigned char value)
    {
        m_byte539 = value;
    }

    const char *cCharacterEntityIF::RetClassName() const
    {
        return "cCharacterEntityIF";
    }

    const char *cCharacterEntityIF::RetMovementType() const
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

    void *cCharacterEntityIF::GetPtr504A0() const
    {
        return &m_pAIEntity->m_vecHeadDirection;
    }

    void *cCharacterEntityIF::GetPtr504B0() const
    {
        return &m_pAIEntity->m_vecEyePosition;
    }

    float cCharacterEntityIF::GetFloat504_90() const
    {
        return m_pAIEntity->m_fViewingDistance;
    }

    float cCharacterEntityIF::GetFloat504_98() const
    {
        return m_pAIEntity->m_fThreatObjectViewingDistance;
    }

    float cCharacterEntityIF::GetFloat504_9C() const
    {
        return m_pAIEntity->m_fHearingAcuteness;
    }

    unsigned char cCharacterEntityIF::GetBool38_50() const
    {
        bool result = (unsigned int)(&m_eNetRole)[-1] != 0 &&
            m_p50 != 0;
        return result;
    }

    unsigned char cCharacterEntityIF::CheckField548() const
    {
        const CHARACTER::cCharacter *character = RetCharacter();
        if (character)
        {
            const unsigned int v = character->m_field548;
            return (0x30000 - (v & 0xFFFF0000)) == 0;
        }
        return 0;
    }

    float cCharacterEntityIF::GetFloatConditional() const
    {
        cCharacterEntity *t = m_pAIEntity;
        cCharacterEntityIF *owner = t->m_pOwner;
        Fun_Runtime::cSafeDeletable *safe = owner->m_pCharacter.m_pPtr;
        const CHARACTER::cCharacter *p = static_cast<const CHARACTER::cCharacter *>(safe);
        if ((p->m_byte1681 & 0x40) != 0)
            return 180.0f;
        return t->m_fViewingAngle;
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cCharacterEntityIFRegistrar(
        "cCharacterEntityIF", cCharacterEntityIF::MakeNew, 0x540, false);
}
