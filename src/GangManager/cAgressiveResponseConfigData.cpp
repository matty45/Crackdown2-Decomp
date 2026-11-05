#include "GangManager/cAgressiveResponseConfigData.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GangManager
{
    // CD2 0x8266F888 (not matched): CD2 also inlines cSafeDeletable's constructor and keeps the object in r3; as in
    // cFactionConfigData::MakeNew, a local inline constructor gives 49% with the object held in r31.
    RWS::CAttributeHandler *cAgressiveResponseConfigData::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgressiveResponseConfigData(packet);
    }

    const char *cAgressiveResponseConfigData::RetClassName() const
    {
        return "cAgressiveResponseConfigData";
    }

    cAgressiveResponseConfigData::~cAgressiveResponseConfigData()
    {
    }

    static RWS::CClassFactory::CRegistrar cAgressiveResponseConfigDataRegistrar(
        "cAgressiveResponseConfigData", cAgressiveResponseConfigData::MakeNew, 0x60, false);
}
