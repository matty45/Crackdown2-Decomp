#include "fun_runtime/retval.h"
#include "CHARACTER/cStrengthSkillProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cStrengthSkillProfile::RetClassName() const
    {
        return "cStrengthSkillProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cStrengthSkillProfileRegistrar(
        "cStrengthSkillProfile", cStrengthSkillProfile::MakeNew, 0x414, false);
}

namespace CHARACTER
{
    Fun_Runtime::RetVal cStrengthSkillProfile::Term()
    {
        return Ret_OK;
    }
}
