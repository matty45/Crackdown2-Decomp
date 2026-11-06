// src/Prop/Custom/cTODSlidingDoor.cpp
//
// Class: cTODSlidingDoor (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cTODSlidingDoor.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cTODSlidingDoor.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cTODSlidingDoor.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cSlidingDoor.h"
#include "rws/classfactory.h"
#include "Prop/cTODSlidingDoor.h"
#include "cd2/memory.h"

namespace Prop
{
    const char *cTODSlidingDoor::RetClassName() const
    {
        return "cTODSlidingDoor";
    }

    Fun_Runtime::cClass &cTODSlidingDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTODSlidingDoorClass = new Fun_Runtime::cClass(0x5D31C, "cTODSlidingDoor", 0xF00);
        return *cTODSlidingDoorClass;
    }

    const Fun_Runtime::cClass *cTODSlidingDoor::ms_pcTODSlidingDoorClass = &cTODSlidingDoor::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cTODSlidingDoorRegistrar(
        "cTODSlidingDoor", cTODSlidingDoor::MakeNew, 0xF00, false);

    // CD2 0x82FFC010: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTODSlidingDoorcSlidingDoorInheritRegistrar(
        Prop::cTODSlidingDoor::StaticCreateClass(), Prop::cSlidingDoor::StaticCreateClass());

    // CD2 0x82FFC0C8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTODSlidingDoorSpawningRegistrar(
        cTODSlidingDoor::StaticCreateClass(), cTODSlidingDoor::SpawnFromPrototype);
}
