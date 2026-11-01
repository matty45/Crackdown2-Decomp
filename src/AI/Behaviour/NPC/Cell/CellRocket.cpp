#include "AI/CellRocket.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellRocket::ms_pCellRocketClass = &CellRocket::StaticCreateClass();

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

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
        "CellRocket", CellRocket::MakeNew, 0x110, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellRocket::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellRocketClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellRocket", 0x110);
        return *CellRocketClass;
    }
}
