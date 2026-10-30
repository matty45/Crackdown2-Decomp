#include "AI/PedestrianInjured.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *PedestrianInjured::ms_pPedestrianInjuredClass = 0;

    PedestrianInjured::PedestrianInjured() {}

    const Fun_Runtime::cClass &PedestrianInjured::RetClass() const
    {
        return *ms_pPedestrianInjuredClass;
    }

    const char *PedestrianInjured::RetClassName() const
    {
        return "PedestrianInjured";
    }

    bool PedestrianInjured::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPedestrianInjuredClass->IsA(c);
    }

    RWS::CAttributeHandler *PedestrianInjured::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new PedestrianInjured();
    }
}

static RWS::CClassFactory::CRegistrar PedestrianInjuredRegistrar(
    "PedestrianInjured", AI::PedestrianInjured::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianInjuredRegistrar(
        "PedestrianInjured", PedestrianInjured::MakeNew, 0x130, false);
}
