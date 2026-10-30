#include "AI/BeaconDropBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *BeaconDropBehaviour::ms_pBeaconDropBehaviourClass = 0;

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
}

static RWS::CClassFactory::CRegistrar BeaconDropBehaviourRegistrar(
    "BeaconDropBehaviour", AI::BeaconDropBehaviour::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar BeaconDropBehaviourRegistrar(
        "BeaconDropBehaviour", BeaconDropBehaviour::MakeNew, 0x150, false);
}
