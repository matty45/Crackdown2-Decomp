// src/AI/Mission/cMissionCriticalProp.cpp
//
// Class: cMissionCriticalProp (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cMissionCriticalProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Mission/cMissionCriticalProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Mission/cMissionCriticalProp.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
#include "AI/cMissionCriticalProp.h"
#include "cd2/memory.h"
#include <new>

namespace AI
{
    RWS::CAttributeHandler *cMissionCriticalProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cMissionCriticalPropPrototype(packet);
    }

    const char *cMissionCriticalProp::RetClassName() const
    {
        return "cMissionCriticalProp";
    }

    RWS::CAttributeHandler *cMissionCriticalProp::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cMissionCriticalProp(pPrototype);
        return 0;
    }

    Fun_Runtime::cClass &cMissionCriticalProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionCriticalPropClass = new Fun_Runtime::cClass(0x409, "cMissionCriticalProp", 0xE40);
        return *cMissionCriticalPropClass;
    }

    Fun_Runtime::RetVal cMissionCriticalProp::cMissionCriticalPropPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    cMissionCriticalProp::cMissionCriticalProp(GOM::cObjectPrototype *prototype)
        : Prop::cProp(prototype), m_bInteractable(true)
    {
    }

    // CD2 0x8245B1E0 has no derived cleanup beyond vtable restoration.
    cMissionCriticalProp::~cMissionCriticalProp()
    {
    }

    Fun_Runtime::RetVal cMissionCriticalProp::Init(const GOM::cSpawner *spawner)
    {
        return Prop::cProp::Init(spawner);
    }

    const Fun_Runtime::cClass *cMissionCriticalProp::ms_pcMissionCriticalPropClass = &cMissionCriticalProp::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cMissionCriticalPropRegistrar(
        "cMissionCriticalProp", cMissionCriticalProp::MakeNew, 0xE40, false);

    // CD2 0x82F872E8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cMissionCriticalPropcPropInheritRegistrar(
        AI::cMissionCriticalProp::StaticCreateClass(), Prop::cProp::StaticCreateClass());

    // CD2 0x82F873A0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cMissionCriticalPropSpawningRegistrar(
        cMissionCriticalProp::StaticCreateClass(), cMissionCriticalProp::SpawnFromPrototype);

}
