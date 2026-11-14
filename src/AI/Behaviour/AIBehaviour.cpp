// src/AI/Behaviour/AIBehaviour.cpp
//
// Class: AIBehaviour (namespace: AI). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is AIBehaviour.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Behaviour/AIBehaviour.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Behaviour/AIBehaviour.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "AI/AIBehaviour.h"
#include "AI/BehaviourClassID.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    const RWS::RWSGUID &AIBehaviour::AIBehaviourPrototype::RetPrimaryWeapon() const
    {
        return Editor::g_GUIDNull;
    }

    const char *AIBehaviour::RetClassName() const
    {
        return "AIBehaviour";
    }

    RWS::CAttributeHandler *AIBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        return new (memory) AIBehaviour;
    }

    const Fun_Runtime::cClass &AIBehaviour::RetClass() const
    {
        return *ms_pAIBehaviourClass;
    }

    const Fun_Runtime::cClass *AIBehaviour::ms_pAIBehaviourClass = &AIBehaviour::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar AIBehaviourcNonGameBaseInheritRegistrar(
        AIBehaviour::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar AIBehaviourRegistrar(
        "AIBehaviour", AIBehaviour::MakeNew, 0x7c, false);

    static GOM::cProtoRegistrar AIBehaviourSpawningRegistrar(
        AIBehaviour::StaticCreateClass(), AIBehaviour::SpawnFromPrototype);

    // CD2 0x824a4a10: the class factory builds the prototype.
    RWS::CAttributeHandler *AIBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new AIBehaviourPrototype(packet);
    }

    Fun_Runtime::cClass &AIBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *AIBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "AIBehaviour", 0x7C);
        return *AIBehaviourClass;
    }
}
