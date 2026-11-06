// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCwCharacter.h"
#include "CHARACTER/cCwGoliathCharacterWrapper.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>

namespace CHARACTER
{
    const char *cCwGoliathCharacterWrapper::RetClassName() const
    {
        return "cCwGoliathCharacterWrapper";
    }

    static RWS::CClassFactory::CRegistrar cCwGoliathCharacterWrapperRegistrar(
        "cCwGoliathCharacterWrapper", cCwGoliathCharacterWrapper::MakeNew, 0x34C0, false);

    RWS::CAttributeHandler *cCwGoliathCharacterWrapper::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cCwGoliathCharacterWrapper(pPrototype);
        return 0;
    }

    Fun_Runtime::cClass &cCwGoliathCharacterWrapper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwGoliathCharacterWrapperClass = new Fun_Runtime::cClass(0x674, "cCwGoliathCharacterWrapper", 0x34C0);
        return *cCwGoliathCharacterWrapperClass;
    }

    const Fun_Runtime::cClass *cCwGoliathCharacterWrapper::ms_pcCwGoliathCharacterWrapperClass = &cCwGoliathCharacterWrapper::StaticCreateClass();

    // CD2 0x82FAD2B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCwGoliathCharacterWrappercCwCharacterInheritRegistrar(
        CHARACTER::cCwGoliathCharacterWrapper::StaticCreateClass(), CHARACTER::cCwCharacter::StaticCreateClass());

    // CD2 0x82FAD370: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCwGoliathCharacterWrapperSpawningRegistrar(
        cCwGoliathCharacterWrapper::StaticCreateClass(), cCwGoliathCharacterWrapper::SpawnFromPrototype);
}
