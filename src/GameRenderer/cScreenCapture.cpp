#include "GameRenderer/cScreenCapture.h"
#include "rws/classfactory.h"

namespace GameRenderer
{
    const char *cScreenCapture::RetClassName() const
    {
        return "cScreenCapture";
    }
}

namespace GameRenderer
{
    static RWS::CClassFactory::CRegistrar cScreenCaptureRegistrar(
        "cScreenCapture", cScreenCapture::MakeNew, 0x1F0, false);
}
