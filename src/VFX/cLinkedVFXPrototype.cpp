#include "rws/classfactory.h"
#include "VFX/cLinkedVFXPrototype.h"

namespace VFX
{
    const char *cLinkedVFXPrototype::RetClassName() const
    {
        return "cLinkedVFXPrototype";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cLinkedVFXPrototypeRegistrar(
        "cLinkedVFXPrototype", cLinkedVFXPrototype::MakeNew, 0x44, false);
}
