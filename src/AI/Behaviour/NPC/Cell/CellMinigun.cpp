#include "AI/CellMinigun.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellMinigun::ms_pCellMinigunClass = 0;

    CellMinigun::CellMinigun() {}

    const Fun_Runtime::cClass &CellMinigun::RetClass() const
    {
        return *ms_pCellMinigunClass;
    }

    const char *CellMinigun::RetClassName() const
    {
        return "CellMinigun";
    }

    bool CellMinigun::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellMinigunClass->IsA(c);
    }

    RWS::CAttributeHandler *CellMinigun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellMinigun();
    }
}

static RWS::CClassFactory::CRegistrar CellMinigunRegistrar(
    "CellMinigun", AI::CellMinigun::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellMinigunRegistrar(
        "CellMinigun", CellMinigun::MakeNew, 0x100, false);
}
