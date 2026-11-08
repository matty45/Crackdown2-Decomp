// Known wrong, left for a structural fix: this file holds two of RuffKing's objects. NPCArmedBehaviour.obj has the initializer run
// from 0x82F913A0 (its header constants, then 0x82F91630 and 0x82F91658) and the code from 0x824A7DD0; NPCBehaviour.obj
// has the run from 0x82F919D0 (to 0x82F91DC0) and the code up to its StaticCreateClass (0x824A87A0). Splitting it
// needs the text boundary between the two objects.

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
#include "gom/proto_registrar.h"
#include "cd2/memory.h"

namespace AI
{
    const char *NPCBehaviour::RetClassName() const
    {
        return "NPCBehaviour";
    }

    // CD2 0x824A7DF0 / 0x824A7E00: slots 0 and 1 of NPCArmedBehaviour's registered-class table (0x82108BD8, which its
    // constructor 0x824A8070 installs); they read the descriptor pointer that 0x82F91630 sets from 0x824A7E80.
    const Fun_Runtime::cClass &NPCArmedBehaviour::RetClass() const
    {
        return *ms_pNPCArmedBehaviourClass;
    }

    bool NPCArmedBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pNPCArmedBehaviourClass->IsA(c);
    }

    Fun_Runtime::cClass &NPCArmedBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *NPCArmedBehaviourClass =
            new Fun_Runtime::cClass(g_nBehaviourClassID++, "NPCArmedBehaviour", 0xF0);
        return *NPCArmedBehaviourClass;
    }

    const Fun_Runtime::cClass *NPCArmedBehaviour::ms_pNPCArmedBehaviourClass = &NPCArmedBehaviour::StaticCreateClass();

    // CD2 0x82F91658: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar NPCArmedBehaviourNPCBehaviourInheritRegistrar(
        AI::NPCArmedBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    NPCBehaviour::NPCBehaviour() {}

    RWS::CAttributeHandler *NPCBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new NPCBehaviour();
    }

    const Fun_Runtime::cClass &NPCBehaviour::RetClass() const
    {
        return *ms_pNPCBehaviourClass;
    }

    bool NPCBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pNPCBehaviourClass->IsA(c);
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
