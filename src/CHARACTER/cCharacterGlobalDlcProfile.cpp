// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterGlobalDlcProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCharacterGlobalDlcProfile::RetClassName() const
    {
        return "cCharacterGlobalDlcProfile";
    }

    static RWS::CClassFactory::CRegistrar cCharacterGlobalDlcProfileRegistrar(
        "cCharacterGlobalDlcProfile", cCharacterGlobalDlcProfile::MakeNew, 0xA8, false);
}
