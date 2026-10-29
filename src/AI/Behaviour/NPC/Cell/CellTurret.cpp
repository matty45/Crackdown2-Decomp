#include "AI/CellTurret.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellTurret::ms_pCellTurretClass = 0;

    CellTurret::CellTurret() {}

    const Fun_Runtime::cClass &CellTurret::RetClass() const
    {
        return *ms_pCellTurretClass;
    }

    const char *CellTurret::RetClassName() const
    {
        return "CellTurret";
    }

    bool CellTurret::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellTurretClass->IsA(c);
    }

    RWS::CAttributeHandler *CellTurret::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellTurret();
    }
}

static RWS::CClassFactory::CRegistrar CellTurretRegistrar(
    "CellTurret", AI::CellTurret::MakeNew, 0x7C, false);
