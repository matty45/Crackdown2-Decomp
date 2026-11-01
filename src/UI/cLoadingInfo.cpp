#include "UI/cLoadingInfo.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace UI
{
    RWS::CAttributeHandler *cLoadingInfo::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cLoadingInfo;
    }

    static RWS::CClassFactory::CRegistrar cLoadingInfoRegistrar(
        "cLoadingInfo", cLoadingInfo::MakeNew, 0x54, false);

    const char *cLoadingInfo::RetClassName() const
    {
        return "cLoadingInfo";
    }
}
