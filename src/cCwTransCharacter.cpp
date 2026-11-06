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

// Not named yet: the fields at 0x2D20..0x2DD0 have no script or reference name. Their accessors (0x82538170..
// 0x82538238) are virtual slots 391..445 of the character tables (0x82018BE8), not declared yet: open.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCharacter.h"
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

    Fun_Runtime::cClass &cCwTransCharacter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwTransCharacterClass = new Fun_Runtime::cClass(0x6A1, "cCwTransCharacter", 0x2E00);
        return *cCwTransCharacterClass;
    }

    const Fun_Runtime::cClass *cCwTransCharacter::ms_pcCwTransCharacterClass = &cCwTransCharacter::StaticCreateClass();

    // CD2 0x82FABCC8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCwTransCharactercCharacterInheritRegistrar(
        CHARACTER::cCwTransCharacter::StaticCreateClass(), CHARACTER::cCharacter::StaticCreateClass());

    // CD2 0x82FABD80: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCwTransCharacterSpawningRegistrar(
        cCwTransCharacter::StaticCreateClass(), cCwTransCharacter::SpawnFromPrototype);
}
