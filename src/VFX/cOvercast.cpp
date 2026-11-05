#include "rws/classfactory.h"
#include "VFX/cOvercast.h"

namespace VFX
{
    const char *cOvercast::RetClassName() const
    {
        return "cOvercast";
    }

    static RWS::CClassFactory::CRegistrar cOvercastRegistrar(
        "cOvercast", cOvercast::MakeNew, 0x48, false);
}
