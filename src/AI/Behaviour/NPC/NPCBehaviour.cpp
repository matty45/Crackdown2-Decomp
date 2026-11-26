// AI/Behaviour/NPC/NPCBehaviour.cpp: RuffKing's Libraries/Shared/AI/Behaviour/NPC/NPCBehaviour.cpp.
// Its text range and the evidence for it are in config/splits.txt.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/AIBehaviour.h"
#include "AI/NPCBehaviour.h"
#include "rws/classfactory.h"
#include "AI/BehaviourClassID.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "AI/NPCBehaviourPrototype.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    NPCBehaviourPrototype::NPCBehaviourPrototype(const RWS::CAttributePacket &packet)
        : AIBehaviour::AIBehaviourPrototype(packet), mPrimary(Editor::g_GUIDNull)
    {
    }

    const RWS::RWSGUID &NPCBehaviourPrototype::RetPrimaryWeapon() const
    {
        return mPrimary;
    }

    // NPCBehaviour's constructor is 0x824A89C8, outside this scaffold's text range.
    RWS::CAttributeHandler *NPCBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        return new (memory) NPCBehaviour;
    }

    RWS::CAttributeHandler *NPCBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new NPCBehaviour();
    }

    const Fun_Runtime::cClass &NPCBehaviour::RetClass() const
    {
        return *ms_pNPCBehaviourClass;
    }

    void NPCBehaviour::OnEnterReplicatedState(unsigned char)
    {
        OnEnter();
    }

    Fun_Runtime::cClass &NPCBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *NPCBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "NPCBehaviour", 0xC0);
        return *NPCBehaviourClass;
    }

    const Fun_Runtime::cClass *NPCBehaviour::ms_pNPCBehaviourClass = &NPCBehaviour::StaticCreateClass();

    // CD2 0x82F91D08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCBehaviourAIBehaviourInheritRegistrar(
        AI::NPCBehaviour::StaticCreateClass(), AI::AIBehaviour::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar NPCBehaviourRegistrar(
        "NPCBehaviour", NPCBehaviour::MakeNew, 0xC0, false);

    static GOM::cProtoRegistrar NPCBehaviourSpawningRegistrar(
        NPCBehaviour::StaticCreateClass(), NPCBehaviour::SpawnFromPrototype);
}
