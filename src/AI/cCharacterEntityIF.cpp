// src/AI/cCharacterEntityIF.cpp
//
// Class: cCharacterEntityIF (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cCharacterEntityIF.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code):
// include/ref/ruffking/AI_cCharacterEntityIF.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/cCharacterEntityIF.cpp

#include "AI/cCharacterEntityIF.h"

namespace AI
{
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
        return reinterpret_cast<void *>(*reinterpret_cast<const unsigned int *>((const char *)this + 0x504) + 0xA0);
    }

    void *cCharacterEntityIF::GetPtr504B0() const
    {
        return reinterpret_cast<void *>(*reinterpret_cast<const unsigned int *>((const char *)this + 0x504) + 0xB0);
    }

    float cCharacterEntityIF::GetFloat504_90() const
    {
        return *reinterpret_cast<const float *>(*reinterpret_cast<const unsigned int *>((const char *)this + 0x504) + 0x90);
    }

    float cCharacterEntityIF::GetFloat504_98() const
    {
        return *reinterpret_cast<const float *>(*reinterpret_cast<const unsigned int *>((const char *)this + 0x504) + 0x98);
    }

    float cCharacterEntityIF::GetFloat504_9C() const
    {
        return *reinterpret_cast<const float *>(*reinterpret_cast<const unsigned int *>((const char *)this + 0x504) + 0x9C);
    }

    unsigned char cCharacterEntityIF::GetBool38_50() const
    {
        bool result = *reinterpret_cast<const unsigned int *>((const char *)this + 0x38) != 0 &&
            *reinterpret_cast<const unsigned int *>((const char *)this + 0x50) != 0;
        return result;
    }

    unsigned char cCharacterEntityIF::CheckField548() const
    {
        const CHARACTER::cCharacter *character = RetCharacter();
        if (character)
        {
            const unsigned int v = *reinterpret_cast<const unsigned int *>((const char *)character + 0x548);
            return (0x30000 - (v & 0xFFFF0000)) == 0;
        }
        return 0;
    }

    float cCharacterEntityIF::GetFloatConditional() const
    {
        const unsigned int t = *reinterpret_cast<const unsigned int *>((const char *)this + 0x504);
        const unsigned int owner = *reinterpret_cast<const unsigned int *>((const char *)t + 0xC8);
        Fun_Runtime::cSafeDeletable *safe = *reinterpret_cast<Fun_Runtime::cSafeDeletable *const *>((const char *)owner + 0x88);
        const CHARACTER::cCharacter *p = static_cast<const CHARACTER::cCharacter *>(safe);
        if ((*reinterpret_cast<const unsigned char *>((const char *)p + 0x1681) & 0x40) != 0)
            return 180.0f;
        return *reinterpret_cast<const float *>((const char *)t + 0x88);
    }
}
