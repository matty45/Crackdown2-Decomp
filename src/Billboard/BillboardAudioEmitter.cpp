// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "Billboard/BillboardAudioEmitter.h"

namespace Billboard
{
    const char *BillboardAudioEmitter::RetClassName() const
    {
        return "BillboardAudioEmitter";
    }

    static RWS::CClassFactory::CRegistrar BillboardAudioEmitterRegistrar(
        "BillboardAudioEmitter", BillboardAudioEmitter::MakeNew, 0x70, false);
}
