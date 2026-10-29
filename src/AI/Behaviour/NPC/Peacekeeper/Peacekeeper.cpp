#include "AI/Peacekeeper.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Peacekeeper::ms_pPeacekeeperClass = 0;

    Peacekeeper::Peacekeeper() {}

    const Fun_Runtime::cClass &Peacekeeper::RetClass() const
    {
        return *ms_pPeacekeeperClass;
    }

    const char *Peacekeeper::RetClassName() const
    {
        return "Peacekeeper";
    }

    bool Peacekeeper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPeacekeeperClass->IsA(c);
    }

    RWS::CAttributeHandler *Peacekeeper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new Peacekeeper();
    }
}

static RWS::CClassFactory::CRegistrar PeacekeeperRegistrar(
    "Peacekeeper", AI::Peacekeeper::MakeNew, 0x7C, false);
