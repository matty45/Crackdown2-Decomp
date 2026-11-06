// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "fun_runtime/retval.h"
#include "CHARACTER/cStrengthSkillProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cStrengthSkillProfile::RetClassName() const
    {
        return "cStrengthSkillProfile";
    }

    static RWS::CClassFactory::CRegistrar cStrengthSkillProfileRegistrar(
        "cStrengthSkillProfile", cStrengthSkillProfile::MakeNew, 0x414, false);

    Fun_Runtime::RetVal cStrengthSkillProfile::Term()
    {
        return Ret_OK;
    }
}
