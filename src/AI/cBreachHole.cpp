#include "AI/cBreachHole.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBreachHole::ms_pcBreachHoleClass = &cBreachHole::StaticCreateClass();

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
    "cBreachHole", AI::cBreachHole::MakeNew, 0x1C0, false);

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cBreachHole::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBreachHoleClass = new Fun_Runtime::cClass(0x9F01F, "cBreachHole", 0x1C0);
        return *cBreachHoleClass;
    }
}
