#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/BeaconDropBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *BeaconDropBehaviour::ms_pBeaconDropBehaviourClass = &BeaconDropBehaviour::StaticCreateClass();

    BeaconDropBehaviour::BeaconDropBehaviour() {}

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
