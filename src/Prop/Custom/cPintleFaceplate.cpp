#include "Prop/cPintleFaceplate.h"
#include "rws/classfactory.h"

namespace Prop
{
    const char *cPintleFaceplate::RetClassName() const
    {
        return "cPintleFaceplate";
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cPintleFaceplateRegistrar(
        "cPintleFaceplate", cPintleFaceplate::MakeNew, 0xE40, false);
}
