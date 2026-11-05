#include "Cam/cCameraMarker.h"
#include "rws/classfactory.h"

namespace Cam
{
    const char *cCameraMarker::RetClassName() const
    {
        return "cCameraMarker";
    }

    static RWS::CClassFactory::CRegistrar cCameraMarkerRegistrar(
        "cCameraMarker", cCameraMarker::MakeNew, 0x80, false);
}
