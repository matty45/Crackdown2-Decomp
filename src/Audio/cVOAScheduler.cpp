#include "rws/classfactory.h"
// src/Audio/cVOAScheduler.cpp
//
// Class: cVOAScheduler (namespace: Audio). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cVOAScheduler.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Audio/cVOAScheduler.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Audio/cVOAScheduler.cpp

#include "Audio/cVOAScheduler.h"

namespace Audio
{
    const char *cVOAScheduler::RetClassName() const
    {
        return "cVOAScheduler";
    }
}

namespace Audio
{
    static RWS::CClassFactory::CRegistrar cVOASchedulerRegistrar(
        "cVOAScheduler", cVOAScheduler::MakeNew, 0x480, false);
}

#include "cd2/memory.h"

// CD2 0x82836E60: the class-factory constructor; the constructor stays out of line.
namespace Audio
{
    RWS::CAttributeHandler *cVOAScheduler::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cVOAScheduler;
    }
}
