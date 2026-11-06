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
#include "AI/cPilotBase.h"
#include "AI/cVehicleCollectionBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleCollectionBehaviour::ms_pcVehicleCollectionBehaviourClass = &cVehicleCollectionBehaviour::StaticCreateClass();

    cVehicleCollectionBehaviour::cVehicleCollectionBehaviour() {}

    const Fun_Runtime::cClass &cVehicleCollectionBehaviour::RetClass() const
    {
        return *ms_pcVehicleCollectionBehaviourClass;
    }

    const char *cVehicleCollectionBehaviour::RetClassName() const
    {
        return "cVehicleCollectionBehaviour";
    }

    bool cVehicleCollectionBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVehicleCollectionBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *cVehicleCollectionBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleCollectionBehaviour();
    }

    static RWS::CClassFactory::CRegistrar cVehicleCollectionBehaviourRegistrar(
        "cVehicleCollectionBehaviour", cVehicleCollectionBehaviour::MakeNew, 0x160, false);

    Fun_Runtime::cClass &cVehicleCollectionBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVehicleCollectionBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cVehicleCollectionBehaviour", 0x160);
        return *cVehicleCollectionBehaviourClass;
    }

    // CD2 0x82F9CE60: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVehicleCollectionBehaviourcPilotBaseInheritRegistrar(
        AI::cVehicleCollectionBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());

    // CD2 0x82F9CF18: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleCollectionBehaviourSpawningRegistrar(
        cVehicleCollectionBehaviour::StaticCreateClass(), cVehicleCollectionBehaviour::SpawnFromPrototype);
}
