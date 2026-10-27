#include "AI/cBreachHole.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBreachHole::ms_pcBreachHoleClass = 0;

    cBreachHole::cBreachHole() {}

    const Fun_Runtime::cClass &cBreachHole::RetClass() const
    {
        return *ms_pcBreachHoleClass;
    }

    const char *cBreachHole::RetClassName() const
    {
        return "cBreachHole";
    }

    bool cBreachHole::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBreachHoleClass->IsA(c);
    }

    RWS::CAttributeHandler *cBreachHole::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBreachHole();
    }
}

static RWS::CClassFactory::CRegistrar cBreachHoleRegistrar(
    "cBreachHole", AI::cBreachHole::MakeNew, 0x7C, false);
