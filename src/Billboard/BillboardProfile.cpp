#include "rws/classfactory.h"
#include "Billboard/BillboardProfile.h"

namespace Billboard
{
    const char *BillboardProfile::RetClassName() const
    {
        return "BillboardProfile";
    }
}

namespace Billboard
{
    static RWS::CClassFactory::CRegistrar BillboardProfileRegistrar(
        "BillboardProfile", BillboardProfile::MakeNew, 0x64, false);
}
