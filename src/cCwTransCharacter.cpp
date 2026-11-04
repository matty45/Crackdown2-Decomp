#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacter.h"
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

// Not named yet: GetByte2D20/2DA4/2DA6, SetByte2DA5/2DA6, GetWord2DD0 and their fields have no script or reference name.
#include "CHARACTER/cCwTransCharacter.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

#include <new>

namespace CHARACTER
{
    RWS::CAttributeHandler *cCwTransCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCwTransCharacterPrototype(packet);
    }

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

namespace CHARACTER
{
    Fun_Runtime::cClass &cCwTransCharacter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwTransCharacterClass = new Fun_Runtime::cClass(0x6A1, "cCwTransCharacter", 0x2E00);
        return *cCwTransCharacterClass;
    }
}

namespace CHARACTER
{
    const Fun_Runtime::cClass *cCwTransCharacter::ms_pcCwTransCharacterClass = &cCwTransCharacter::StaticCreateClass();
}

// CD2 0x82FABCC8: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cCwTransCharactercCharacterInheritRegistrar(
        CHARACTER::cCwTransCharacter::StaticCreateClass(), CHARACTER::cCharacter::StaticCreateClass());
}

// CD2 0x82FABD80: register the class descriptor and placement factory.
namespace CHARACTER
{
    static GOM::cProtoRegistrar cCwTransCharacterSpawningRegistrar(
        cCwTransCharacter::StaticCreateClass(), cCwTransCharacter::SpawnFromPrototype);
}
