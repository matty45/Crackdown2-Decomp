// src/AI/Behaviour/NPC/Freak/Goliath.cpp
//
// Class: Goliath (namespace: AI). Set up automatically: no function is matched yet. The address range and the evidence
// for it are in config/splits.txt; RuffKing's object for it is Goliath.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Behaviour/NPC/Freak/Goliath.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Behaviour/NPC/Freak/Goliath.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cChaseBehaviour.h"
#include "rws/classfactory.h"
#include "AI/Goliath.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const char *Goliath::RetClassName() const
    {
        return "Goliath";
    }

    Fun_Runtime::cClass &Goliath::StaticCreateClass()
    {
        static Fun_Runtime::cClass *GoliathClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Goliath", 0x100);
        return *GoliathClass;
    }

    const Fun_Runtime::cClass *Goliath::ms_pGoliathClass = &Goliath::StaticCreateClass();

    const Fun_Runtime::cClass &Goliath::RetClass() const
    {
        return *ms_pGoliathClass;
    }

    bool Goliath::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pGoliathClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar GoliathRegistrar(
        "Goliath", Goliath::MakeNew, 0x100, false);

    // CD2 0x82F93AA0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar GoliathNPCBehaviourSMInheritRegistrar(
        AI::Goliath::StaticCreateClass(), AI::NPCBehaviourSM::StaticCreateClass());

    // CD2 0x82F93B58: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar GoliathSpawningRegistrar(
        Goliath::StaticCreateClass(), Goliath::SpawnFromPrototype);
}
