#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
#include "rws/classfactory.h"
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

#include "AI/cMissionCriticalProp.h"

namespace AI
{
    const char *cMissionCriticalProp::RetClassName() const
    {
        return "cMissionCriticalProp";
    }
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cMissionCriticalProp::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cMissionCriticalPropClass = new Fun_Runtime::cClass(0x409, "cMissionCriticalProp", 0xE40);
        return *cMissionCriticalPropClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cMissionCriticalProp::ms_pcMissionCriticalPropClass = &cMissionCriticalProp::StaticCreateClass();
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cMissionCriticalPropRegistrar(
        "cMissionCriticalProp", cMissionCriticalProp::MakeNew, 0xE40, false);
}

// CD2 0x82F872E8: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cMissionCriticalPropcPropInheritRegistrar(
        AI::cMissionCriticalProp::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

#include <new>

// CD2 0x8245AF48: placement factory; the constructor stays out of line (a tail call).
namespace AI
{
    RWS::CAttributeHandler *cMissionCriticalProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cMissionCriticalProp(prototype);
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F873A0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cMissionCriticalPropSpawningRegistrar(
        cMissionCriticalProp::StaticCreateClass(), cMissionCriticalProp::SpawnFromPrototype);
}
