#include "AI/cDocksMission.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cDocksMission::RetClassName() const
    {
        return "cDocksMission";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cDocksMissionRegistrar(
        "cDocksMission", cDocksMission::MakeNew, 0x450, false);
}
