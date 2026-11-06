// src/AI/Mission/cPlayerRejectionZone.cpp
//
// Class: cPlayerRejectionZone (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cPlayerRejectionZone.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/cPlayerRejectionZone.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/cPlayerRejectionZone.cpp


// CD2 0x8248B970.

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "AI/cPlayerRejectionZone.h"

namespace AI
{
    const char *cPlayerRejectionZone::RetClassName() const
    {
        return "cPlayerRejectionZone";
    }

    // CD2 0x8248B9D0: only the member's and the bases' destruction.
    cPlayerRejectionZone::~cPlayerRejectionZone()
    {
    }

    // CD2 0x82F8FD58 (initializer) and 0x8303B2F8 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cPlayerRejectionZoneRegistrar(
        "cPlayerRejectionZone", cPlayerRejectionZone::MakeNew, 0x100, false);
}
