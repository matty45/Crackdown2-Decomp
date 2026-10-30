#include "AI/cGoliathBreachHole.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cGoliathBreachHole::ms_pcGoliathBreachHoleClass = 0;

    cGoliathBreachHole::cGoliathBreachHole() {}

    const Fun_Runtime::cClass &cGoliathBreachHole::RetClass() const
    {
        return *ms_pcGoliathBreachHoleClass;
    }

    const char *cGoliathBreachHole::RetClassName() const
    {
        return "cGoliathBreachHole";
    }

    bool cGoliathBreachHole::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcGoliathBreachHoleClass->IsA(c);
    }

    RWS::CAttributeHandler *cGoliathBreachHole::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGoliathBreachHole();
    }
}

static RWS::CClassFactory::CRegistrar cGoliathBreachHoleRegistrar(
    "cGoliathBreachHole", AI::cGoliathBreachHole::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar cGoliathBreachHoleRegistrar(
        "cGoliathBreachHole", cGoliathBreachHole::MakeNew, 0x1D0, false);
}
