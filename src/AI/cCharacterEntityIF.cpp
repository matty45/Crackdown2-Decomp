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
}
