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
