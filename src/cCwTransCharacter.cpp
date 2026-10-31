// src/cCwTransCharacter.cpp
//
// Class: CHARACTER::cCwTransCharacter. Accessors and registration are reconstructed below.
// The address range and ownership evidence are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cCwTransCharacter.cpp

#include "CHARACTER/cCwTransCharacter.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

inline void *operator new(size_t, void *memory) { return memory; }

namespace CHARACTER
{
    RWS::CAttributeHandler *cCwTransCharacter::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cCwTransCharacter(prototype);
        return 0;
    }

    static RWS::CClassFactory::CRegistrar cCwTransCharacterRegistrar(
        "cCwTransCharacter", cCwTransCharacter::MakeNew, 0x2E00, false);

    const char *cCwTransCharacter::RetClassName() const
    {
        return "cCwTransCharacter";
    }

    unsigned char cCwTransCharacter::GetByte2D20() const
    {
        return m_byte2D20;
    }

    bool cCwTransCharacter::TestFlag2D64(unsigned int bit) const
    {
        return (m_flags2D64 & (1 << bit)) != 0;
    }

    unsigned char cCwTransCharacter::GetByte2DA4() const
    {
        return m_byte2DA4;
    }

    unsigned char cCwTransCharacter::GetByte2DA6() const
    {
        return m_byte2DA6;
    }

    void cCwTransCharacter::SetByte2DA6(unsigned char value)
    {
        m_byte2DA6 = value;
    }

    void cCwTransCharacter::SetByte2DA5(unsigned char value)
    {
        m_byte2DA5 = value;
    }

    unsigned int cCwTransCharacter::GetWord2DD0() const
    {
        return m_word2DD0;
    }
}
