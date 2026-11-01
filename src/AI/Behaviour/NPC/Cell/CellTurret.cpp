#include "AI/CellTurret.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellTurret::ms_pCellTurretClass = &CellTurret::StaticCreateClass();

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

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellTurretRegistrar(
        "CellTurret", CellTurret::MakeNew, 0x100, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellTurret::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellTurretClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellTurret", 0x100);
        return *CellTurretClass;
    }
}
