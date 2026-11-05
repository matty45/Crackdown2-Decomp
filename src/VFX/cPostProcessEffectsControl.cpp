#include "rws/classfactory.h"
#include "VFX/cPostProcessEffectsControl.h"

namespace VFX
{
    const char *cPostProcessEffectsControl::RetClassName() const
    {
        return "cPostProcessEffectsControl";
    }

    static RWS::CClassFactory::CRegistrar cPostProcessEffectsControlRegistrar(
        "cPostProcessEffectsControl", cPostProcessEffectsControl::MakeNew, 0x1c, false);
}
