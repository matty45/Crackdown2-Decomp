#include "GangManager/cAgressiveResponseConfigData.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cAgressiveResponseConfigData::RetClassName() const
    {
        return "cAgressiveResponseConfigData";
    }
}

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cAgressiveResponseConfigDataRegistrar(
        "cAgressiveResponseConfigData", cAgressiveResponseConfigData::MakeNew, 0x60, false);
}
