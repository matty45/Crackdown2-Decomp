#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GameRenderer/cScreenCapture.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace GameRenderer
{
    const char *cScreenCapture::RetClassName() const
    {
        return "cScreenCapture";
    }

    static RWS::CClassFactory::CRegistrar cScreenCaptureRegistrar(
        "cScreenCapture", cScreenCapture::MakeNew, 0x1F0, false);

    // CD2 0x826657A0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cScreenCapture::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cScreenCapture;
    }
}
