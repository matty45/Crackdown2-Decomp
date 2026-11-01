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

#include "Prop/cHingedSpawnDoor.h"

namespace Prop
{
    const char *cHingedSpawnDoor::RetClassName() const
    {
        return "cHingedSpawnDoor";
    }
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cHingedSpawnDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedSpawnDoorClass = new Fun_Runtime::cClass(0x13880, "cHingedSpawnDoor", 0xEE0);
        return *cHingedSpawnDoorClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cHingedSpawnDoor::ms_pcHingedSpawnDoorClass = &cHingedSpawnDoor::StaticCreateClass();
}
