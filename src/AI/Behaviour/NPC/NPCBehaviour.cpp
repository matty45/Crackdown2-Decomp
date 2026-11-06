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
#include "AI/NPCArmedBehaviour.h"
#include "AI/BehaviourClassID.h"
#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &NPCArmedBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *NPCArmedBehaviourClass =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "NPCArmedBehaviour", 0xF0);
        return *NPCArmedBehaviourClass;
    }

    const Fun_Runtime::cClass *NPCBehaviour::ms_pNPCBehaviourClass = 0;

    NPCBehaviour::NPCBehaviour() {}

    const Fun_Runtime::cClass &NPCBehaviour::RetClass() const
    {
        return *ms_pNPCBehaviourClass;
    }

    const char *NPCBehaviour::RetClassName() const
    {
        return "NPCBehaviour";
    }

    bool NPCBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pNPCBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *NPCBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new NPCBehaviour();
    }

    static RWS::CClassFactory::CRegistrar NPCBehaviourRegistrar(
        "NPCBehaviour", NPCBehaviour::MakeNew, 0xC0, false);

    // CD2 0x82F91D08: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCBehaviourAIBehaviourInheritRegistrar(
        AI::NPCBehaviour::StaticCreateClass(), AI::AIBehaviour::StaticCreateClass());

    // CD2 0x82F91658: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCArmedBehaviourNPCBehaviourInheritRegistrar(
        AI::NPCArmedBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}
