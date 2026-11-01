#include "rws/classfactory.h"
#include "VFX/cScatterMeshResources.h"

namespace VFX
{
    const char *cScatterMeshResources::RetClassName() const
    {
        return "cScatterMeshResources";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cScatterMeshResourcesRegistrar(
        "cScatterMeshResources", cScatterMeshResources::MakeNew, 0x1c, false);
}
