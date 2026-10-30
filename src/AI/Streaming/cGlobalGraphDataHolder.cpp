#include "AI/cGlobalGraphDataHolder.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cGlobalGraphDataHolder::RetClassName() const
    {
        return "cGlobalGraphDataHolder";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cGlobalGraphDataHolderRegistrar(
        "cGlobalGraphDataHolder", cGlobalGraphDataHolder::MakeNew, 0x18, false);
}
