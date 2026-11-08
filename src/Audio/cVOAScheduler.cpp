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

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "Audio/cVOAScheduler.h"
#include "cd2/memory.h"

namespace Audio
{
    const char *cVOAScheduler::RetClassName() const
    {
        return "cVOAScheduler";
    }

    const Fun_Runtime::cClass *cVOAScheduler::ms_pcVOASchedulerClass = &cVOAScheduler::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cVOASchedulerRegistrar(
        "cVOAScheduler", cVOAScheduler::MakeNew, 0x480, false);

    const Fun_Runtime::cClass &cVOAScheduler::RetClass() const
    {
        return *ms_pcVOASchedulerClass;
    }

    bool cVOAScheduler::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVOASchedulerClass->IsA(c);
    }

    cVOAScheduler::~cVOAScheduler()
    {
        UnLinkMsg(RWS::iMsgRunningTick);
        ms_pInstance = 0;
    }

    RWS::CAttributeHandler *cVOAScheduler::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cVOAScheduler;
    }
}
