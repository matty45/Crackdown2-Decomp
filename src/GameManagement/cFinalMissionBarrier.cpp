#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cFinalMissionBarrier.h"

namespace GameManagement
{
    const char *cFinalMissionBarrier::RetClassName() const
    {
        return "cFinalMissionBarrier";
    }

    static RWS::CClassFactory::CRegistrar cFinalMissionBarrierRegistrar(
        "cFinalMissionBarrier", cFinalMissionBarrier::MakeNew, 0x80, false);
}
