// src/Prop/Custom/cSlidingDoor.cpp
//
// Class: cSlidingDoor (namespace: Prop). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSlidingDoor.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cSlidingDoor.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cSlidingDoor.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "rws/classfactory.h"
#include "Prop/cSlidingDoor.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Prop
{
    const char *cSlidingDoor::RetClassName() const
    {
        return "cSlidingDoor";
    }

    static RWS::CClassFactory::CRegistrar cSlidingDoorRegistrar(
        "cSlidingDoor", cSlidingDoor::MakeNew, 0xf00, false);

    // CD2 0x827468e8: the class factory builds the prototype.
    RWS::CAttributeHandler *cSlidingDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSlidingDoorPrototype(packet);
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cSlidingDoor> cSlidingDoorScriptRegistrar(
        "cSlidingDoor", "cPrismaticProp");
}
