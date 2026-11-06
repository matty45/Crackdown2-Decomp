// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cAnimParams.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAnimParams::ms_pcAnimParamsClass = 0;

    cAnimParams::cAnimParams() {}

    const Fun_Runtime::cClass &cAnimParams::RetClass() const
    {
        return *ms_pcAnimParamsClass;
    }

    const char *cAnimParams::RetClassName() const
    {
        return "cAnimParams";
    }

    bool cAnimParams::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAnimParamsClass->IsA(c);
    }

    RWS::CAttributeHandler *cAnimParams::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAnimParams();
    }
}

static RWS::CClassFactory::CRegistrar cAnimParamsRegistrar(
    "cAnimParams", AI::cAnimParams::MakeNew, 0x48, false);
