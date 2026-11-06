// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "Equip/cUVLightAttachmentData.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cUVLightAttachmentData::RetClassName() const
    {
        return "cUVLightAttachmentData";
    }

    static RWS::CClassFactory::CRegistrar cUVLightAttachmentDataRegistrar(
        "cUVLightAttachmentData", cUVLightAttachmentData::MakeNew, 0x3C, false);
}
