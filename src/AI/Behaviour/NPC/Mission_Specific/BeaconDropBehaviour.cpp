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
#include "AI/BeaconDropBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass *BeaconDropBehaviour::ms_pBeaconDropBehaviourClass = &BeaconDropBehaviour::StaticCreateClass();

    RWS::CAttributeHandler *BeaconDropBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) BeaconDropBehaviour;
        return 0;
    }

    const Fun_Runtime::cClass &BeaconDropBehaviour::RetClass() const
    {
        return *ms_pBeaconDropBehaviourClass;
    }

    const char *BeaconDropBehaviour::RetClassName() const
    {
        return "BeaconDropBehaviour";
    }

    bool BeaconDropBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pBeaconDropBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *BeaconDropBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new BeaconDropBehaviour();
    }

    static RWS::CClassFactory::CRegistrar BeaconDropBehaviourRegistrar(
        "BeaconDropBehaviour", BeaconDropBehaviour::MakeNew, 0x150, false);

    Fun_Runtime::cClass &BeaconDropBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *BeaconDropBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "BeaconDropBehaviour", 0x150);
        return *BeaconDropBehaviourClass;
    }

    // CD2 0x82F97F48: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar BeaconDropBehaviourcPilotBaseInheritRegistrar(
        AI::BeaconDropBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());

    // CD2 0x82F98000: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar BeaconDropBehaviourSpawningRegistrar(
        BeaconDropBehaviour::StaticCreateClass(), BeaconDropBehaviour::SpawnFromPrototype);
}
