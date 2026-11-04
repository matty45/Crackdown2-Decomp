#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacterMotion.h"
// src/CHARACTER/cCharacter.cpp
//
// Class: CHARACTER::cCharacter. Script flag getters and registration are reconstructed below.
// The address range and ownership evidence are in config/splits.txt; RuffKing's object is cCharacter.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Character/cCharacter.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CHARACTER/cCharacter.cpp

#include "CHARACTER/cCharacter.h"
#include "CHARACTER/cCharacterInterface.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    RWS::CAttributeHandler *cCharacter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCharacterPrototype(packet);
    }

    const char *cCharacter::RetClassName() const
    {
        return "cCharacter";
    }

    bool cCharacter::IsInGodMode() const
    {
        return (m_flags2815 & 0x20) != 0;
    }

    bool cCharacter::IsInfiniteAmmo() const
    {
        return (m_flags2815 & 0x10) != 0;
    }

    // Linker-folded interface getter; this address is owned by this translation unit.
    bool cCharacterInterface::CanBePickedUpWhenAlive() const
    {
        return m_bCanBePickedUpWhenAlive;
    }

    static RWS::CClassFactory::CRegistrar cCharacterRegistrar(
        "cCharacter", cCharacter::MakeNew, 0x2CC0, false);
}

namespace CHARACTER
{
    Fun_Runtime::cClass &cCharacter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCharacterClass = new Fun_Runtime::cClass(0x0, "cCharacter", 0x2CC0);
        return *cCharacterClass;
    }
}

namespace CHARACTER
{
    const Fun_Runtime::cClass *cCharacter::ms_pcCharacterClass = &cCharacter::StaticCreateClass();
}

// CD2 0x82FAD6F0: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cCharactercCharacterMotionInheritRegistrar(
        CHARACTER::cCharacter::StaticCreateClass(), CHARACTER::cCharacterMotion::StaticCreateClass());
}

// CD2 0x82FAD7A8: register the class descriptor and placement factory.
namespace CHARACTER
{
    static GOM::cProtoRegistrar cCharacterSpawningRegistrar(
        cCharacter::StaticCreateClass(), cCharacter::SpawnFromPrototype);
}
