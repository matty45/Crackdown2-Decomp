#include "rws/classfactory.h"
#include "VFX/cReflectionMesh.h"

namespace VFX
{
    const char *cReflectionMesh::RetClassName() const
    {
        return "cReflectionMesh";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cReflectionMeshRegistrar(
        "cReflectionMesh", cReflectionMesh::MakeNew, 0x20, false);
}
