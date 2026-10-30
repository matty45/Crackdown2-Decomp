#include "AI/cVehicleAttackedRockingBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleAttackedRockingBehaviour::ms_pcVehicleAttackedRockingBehaviourClass = 0;

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
}

static RWS::CClassFactory::CRegistrar cVehicleAttackedRockingBehaviourRegistrar(
    "cVehicleAttackedRockingBehaviour", AI::cVehicleAttackedRockingBehaviour::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cVehicleAttackedRockingBehaviourRegistrar(
        "cVehicleAttackedRockingBehaviour", cVehicleAttackedRockingBehaviour::MakeNew, 0xD0, false);
}
