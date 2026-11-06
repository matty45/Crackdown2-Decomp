// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Audio/cWorldGameObjectPosition.h"
#include "rws/classfactory.h"

namespace Audio
{
    const Fun_Runtime::cClass *cWorldGameObjectPosition::ms_pcWorldGameObjectPositionClass = 0;

    cWorldGameObjectPosition::cWorldGameObjectPosition() {}

    const Fun_Runtime::cClass &cWorldGameObjectPosition::RetClass() const
    {
        return *ms_pcWorldGameObjectPositionClass;
    }

    const char *cWorldGameObjectPosition::RetClassName() const
    {
        return "cWorldGameObjectPosition";
    }

    bool cWorldGameObjectPosition::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcWorldGameObjectPositionClass->IsA(c);
    }

    RWS::CAttributeHandler *cWorldGameObjectPosition::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWorldGameObjectPosition();
    }
}

static RWS::CClassFactory::CRegistrar cWorldGameObjectPositionRegistrar(
    "cWorldGameObjectPosition", Audio::cWorldGameObjectPosition::MakeNew, 0x50, false);   // CD2 0x83013B88
