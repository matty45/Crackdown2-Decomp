// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Equip/cLightAttachmentData.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cLightAttachmentData::RetClassName() const
    {
        return "cLightAttachmentData";
    }

    static RWS::CClassFactory::CRegistrar cLightAttachmentDataRegistrar(
        "cLightAttachmentData", cLightAttachmentData::MakeNew, 0x38, false);
}
