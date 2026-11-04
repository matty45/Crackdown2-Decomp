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

#include "cd2/memory.h"

// CD2 0x826657A0: the class-factory constructor; the constructor stays out of line.
namespace GameRenderer
{
    RWS::CAttributeHandler *cScreenCapture::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cScreenCapture;
    }
}
