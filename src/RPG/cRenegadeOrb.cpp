// src/RPG/cRenegadeOrb.cpp
//
// Class: cRenegadeOrb (namespace: RPG). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cRenegadeOrb.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/RPG/cRenegadeOrb.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/RPG/cRenegadeOrb.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cBody.h"
#include "rws/classfactory.h"
#include "RPG/cRenegadeOrb.h"
#include "cd2/memory.h"

namespace RPG
{
    const Fun_Runtime::cClass *cRenegadeOrb::ms_pcRenegadeOrbClass = &cRenegadeOrb::StaticCreateClass();

    Fun_Runtime::cClass &cRenegadeOrb::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRenegadeOrbClass = new Fun_Runtime::cClass(0x67B, "cRenegadeOrb", 0x3B0);
        return *cRenegadeOrbClass;
    }

    static RWS::CClassFactory::CRegistrar cRenegadeOrbRegistrar(
        "cRenegadeOrb", cRenegadeOrb::MakeNew, 0x3B0, false);

    // CD2 0x82FFE510: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cRenegadeOrbcBodyInheritRegistrar(
        RPG::cRenegadeOrb::StaticCreateClass(), PHYSICS::cBody::StaticCreateClass());

    // CD2 0x82FFE5C8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cRenegadeOrbSpawningRegistrar(
        cRenegadeOrb::StaticCreateClass(), cRenegadeOrb::SpawnFromPrototype);

    const char *cRenegadeOrb::RetClassName() const
    {
        return "cRenegadeOrb";
    }

    RWS::CAttributeHandler *cRenegadeOrb::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cRenegadeOrb;
        return 0;
    }
}
