#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCwCharacter.h"
#include "CHARACTER/cCwGoliathCharacterWrapper.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cCwGoliathCharacterWrapper::RetClassName() const
    {
        return "cCwGoliathCharacterWrapper";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cCwGoliathCharacterWrapperRegistrar(
        "cCwGoliathCharacterWrapper", cCwGoliathCharacterWrapper::MakeNew, 0x34C0, false);
}

#include "cd2/memory.h"

namespace CHARACTER
{
    Fun_Runtime::cClass &cCwGoliathCharacterWrapper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwGoliathCharacterWrapperClass = new Fun_Runtime::cClass(0x674, "cCwGoliathCharacterWrapper", 0x34C0);
        return *cCwGoliathCharacterWrapperClass;
    }
}

namespace CHARACTER
{
    const Fun_Runtime::cClass *cCwGoliathCharacterWrapper::ms_pcCwGoliathCharacterWrapperClass = &cCwGoliathCharacterWrapper::StaticCreateClass();
}

// CD2 0x82FAD2B8: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cCwGoliathCharacterWrappercCwCharacterInheritRegistrar(
        CHARACTER::cCwGoliathCharacterWrapper::StaticCreateClass(), CHARACTER::cCwCharacter::StaticCreateClass());
}
