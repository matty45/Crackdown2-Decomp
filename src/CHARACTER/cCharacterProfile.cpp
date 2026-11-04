#include "fun_runtime/retval.h"
#include "CHARACTER/cCharacterProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCharacterProfile::RetClassName() const
    {
        return "cCharacterProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cCharacterProfileRegistrar(
        "cCharacterProfile", cCharacterProfile::MakeNew, 0x260, false);
}

namespace CHARACTER
{
    Fun_Runtime::RetVal cCharacterProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}

#include "cd2/memory.h"

// CD2 0x82553190: the class-factory constructor; the constructor stays out of line.
namespace CHARACTER
{
    RWS::CAttributeHandler *cCharacterProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCharacterProfile;
    }
}
