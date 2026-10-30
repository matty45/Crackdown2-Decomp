#include "AI/cVehicleCollectionBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleCollectionBehaviour::ms_pcVehicleCollectionBehaviourClass = 0;

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
}

static RWS::CClassFactory::CRegistrar cVehicleCollectionBehaviourRegistrar(
    "cVehicleCollectionBehaviour", AI::cVehicleCollectionBehaviour::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cVehicleCollectionBehaviourRegistrar(
        "cVehicleCollectionBehaviour", cVehicleCollectionBehaviour::MakeNew, 0x160, false);
}
