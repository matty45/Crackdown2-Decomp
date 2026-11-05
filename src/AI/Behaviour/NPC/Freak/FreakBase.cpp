// src/AI/Behaviour/NPC/Freak/FreakBase.cpp
//
// Class: FreakBase (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is FreakBase.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Behaviour/NPC/Freak/FreakBase.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Behaviour/NPC/Freak/FreakBase.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cChaseBehaviour.h"
#include "rws/classfactory.h"
#include "AI/FreakBase.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const char *FreakBase::RetClassName() const
    {
        return "FreakBase";
    }

    Fun_Runtime::cClass &FreakBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *FreakBaseClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "FreakBase", 0x120);
        return *FreakBaseClass;
    }

    const Fun_Runtime::cClass *FreakBase::ms_pFreakBaseClass = &FreakBase::StaticCreateClass();

    const Fun_Runtime::cClass &FreakBase::RetClass() const
    {
        return *ms_pFreakBaseClass;
    }

    bool FreakBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pFreakBaseClass->IsA(c);
    }

    RWS::CAttributeHandler *FreakBase::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) FreakBase;
        return 0;
    }

    static RWS::CClassFactory::CRegistrar FreakBaseRegistrar(
        "FreakBase", FreakBase::MakeNew, 0x120, false);

    // CD2 0x82F93668: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar FreakBaseNPCBehaviourSMInheritRegistrar(
        AI::FreakBase::StaticCreateClass(), AI::NPCBehaviourSM::StaticCreateClass());

    // CD2 0x82F93720: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar FreakBaseSpawningRegistrar(
        FreakBase::StaticCreateClass(), FreakBase::SpawnFromPrototype);
}
