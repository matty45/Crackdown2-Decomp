// src/Activity/LongDistanceProps/cLongDistancePropManager.cpp
//
// Class: cLongDistancePropManager (namespace: Activity). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cLongDistancePropManager.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/ActivityManager/LongDistanceProps/cLongDistancePropManager.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Activity/LongDistanceProps/cLongDistancePropManager.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "Activity/cLongDistancePropManager.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace Activity
{
    const Fun_Runtime::cClass &cLongDistancePropManager::RetClass() const
    {
        return *ms_pcLongDistancePropManagerClass;
    }

    bool cLongDistancePropManager::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcLongDistancePropManagerClass->IsA(c);
    }

    RWS::CAttributeHandler *cLongDistancePropManager::MakeNew(const RWS::CAttributePacket &attr, bool)
    {
        return new cLongDistancePropManager(attr);
    }

    cLongDistancePropManager::~cLongDistancePropManager()
    {
        UnLinkMsg(RWS::iMsgRunningTick);
    }

    const char *cLongDistancePropManager::RetClassName() const
    {
        return "cLongDistancePropManager";
    }

    Fun_Runtime::cClass &cLongDistancePropManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLongDistancePropManagerClass = new Fun_Runtime::cClass(0x199F, "cLongDistancePropManager", 0x94);
        return *cLongDistancePropManagerClass;
    }

    const Fun_Runtime::cClass *cLongDistancePropManager::ms_pcLongDistancePropManagerClass = &cLongDistancePropManager::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cLongDistancePropManagercNonGameBaseInheritRegistrar(
        cLongDistancePropManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cLongDistancePropManagerRegistrar(
        "cLongDistancePropManager", cLongDistancePropManager::MakeNew, 0x94, false);
}
