// src/Prop/Custom/cHingedSpawnDoor.cpp
//
// Class: cHingedSpawnDoor (namespace: Prop). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cHingedSpawnDoor.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cHingedSpawnDoor.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cHingedSpawnDoor.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include <new>
#include "rws/classfactory.h"
#include "Prop/cHingedSpawnDoor.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Prop
{
    const char *cHingedSpawnDoor::RetClassName() const
    {
        return "cHingedSpawnDoor";
    }

    Fun_Runtime::cClass &cHingedSpawnDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedSpawnDoorClass = new Fun_Runtime::cClass(0x13880, "cHingedSpawnDoor", 0xEE0);
        return *cHingedSpawnDoorClass;
    }

    const Fun_Runtime::cClass *cHingedSpawnDoor::ms_pcHingedSpawnDoorClass = &cHingedSpawnDoor::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cHingedSpawnDoorRegistrar(
        "cHingedSpawnDoor", cHingedSpawnDoor::MakeNew, 0xEE0, false);

    RWS::CAttributeHandler *cHingedSpawnDoor::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cHingedSpawnDoor(prototype);
        return 0;
    }

    // CD2 0x82FFB2D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHingedSpawnDoorcHingedPropInheritRegistrar(
        Prop::cHingedSpawnDoor::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());

    // CD2 0x82FFB390: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHingedSpawnDoorSpawningRegistrar(
        cHingedSpawnDoor::StaticCreateClass(), cHingedSpawnDoor::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHingedSpawnDoor> cHingedSpawnDoorScriptRegistrar(
        "cHingedSpawnDoor", "cHingedProp");

    const Fun_Runtime::cScriptTypeRegistration *cHingedSpawnDoor::RetScriptTypeRegistration() const
    {
        return &cHingedSpawnDoorScriptRegistrar;
    }
}
