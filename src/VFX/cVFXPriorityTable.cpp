#include "VFX/cVFXPriorityTable.h"
#include "rws/classfactory.h"

namespace VFX
{
    const char *cVFXPriorityTable::RetClassName() const
    {
        return "cVFXPriorityTable";
    }

    RWS::CAttributeHandler *cVFXPriorityTable::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cVFXPriorityTable *p = new cVFXPriorityTable();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cVFXPriorityTableRegistrar(
        "cVFXPriorityTable", cVFXPriorityTable::MakeNew, 0x18, false);
}
