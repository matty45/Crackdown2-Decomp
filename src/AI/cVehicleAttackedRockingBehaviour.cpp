// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cVehicleAttackedRockingBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleAttackedRockingBehaviour::ms_pcVehicleAttackedRockingBehaviourClass = &cVehicleAttackedRockingBehaviour::StaticCreateClass();

    cVehicleAttackedRockingBehaviour::cVehicleAttackedRockingBehaviour() {}

    const Fun_Runtime::cClass &cVehicleAttackedRockingBehaviour::RetClass() const
    {
        return *ms_pcVehicleAttackedRockingBehaviourClass;
    }

    const char *cVehicleAttackedRockingBehaviour::RetClassName() const
    {
        return "cVehicleAttackedRockingBehaviour";
    }

    bool cVehicleAttackedRockingBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVehicleAttackedRockingBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *cVehicleAttackedRockingBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleAttackedRockingBehaviour();
    }

    static RWS::CClassFactory::CRegistrar cVehicleAttackedRockingBehaviourRegistrar(
        "cVehicleAttackedRockingBehaviour", cVehicleAttackedRockingBehaviour::MakeNew, 0xD0, false);

    Fun_Runtime::cClass &cVehicleAttackedRockingBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVehicleAttackedRockingBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cVehicleAttackedRockingBehaviour", 0xD0);
        return *cVehicleAttackedRockingBehaviourClass;
    }

    // CD2 0x82F9A540: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVehicleAttackedRockingBehaviourNPCBehaviourInheritRegistrar(
        AI::cVehicleAttackedRockingBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F9A5F8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleAttackedRockingBehaviourSpawningRegistrar(
        cVehicleAttackedRockingBehaviour::StaticCreateClass(), cVehicleAttackedRockingBehaviour::SpawnFromPrototype);
}
