#include "AI/CellMinigun.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellMinigun::ms_pCellMinigunClass = &CellMinigun::StaticCreateClass();

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

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellMinigunRegistrar(
        "CellMinigun", CellMinigun::MakeNew, 0x100, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellMinigun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellMinigunClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellMinigun", 0x100);
        return *CellMinigunClass;
    }
}
