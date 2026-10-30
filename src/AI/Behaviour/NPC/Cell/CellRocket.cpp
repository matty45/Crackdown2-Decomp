#include "AI/CellRocket.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellRocket::ms_pCellRocketClass = 0;

    CellRocket::CellRocket() {}

    const Fun_Runtime::cClass &CellRocket::RetClass() const
    {
        return *ms_pCellRocketClass;
    }

    const char *CellRocket::RetClassName() const
    {
        return "CellRocket";
    }

    bool CellRocket::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellRocketClass->IsA(c);
    }

    RWS::CAttributeHandler *CellRocket::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellRocket();
    }
}

static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
    "CellRocket", AI::CellRocket::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
        "CellRocket", CellRocket::MakeNew, 0x110, false);
}
