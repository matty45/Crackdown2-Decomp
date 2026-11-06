// src/CHARACTER/cCwCharacterWrapper.cpp
//
// Class: cCwCharacterWrapper (namespace: CHARACTER). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cCwCharacterWrapper.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Character/cCwCharacterWrapper.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/CHARACTER/cCwCharacterWrapper.cpp

#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCwCharacter.h"
#include "rws/classfactory.h"
#include "CHARACTER/cCwCharacterWrapper.h"
#include "cd2/memory.h"
#include <new>

namespace CHARACTER
{
    const char *cCwCharacterWrapper::RetClassName() const
    {
        return "cCwCharacterWrapper";
    }

    RWS::CAttributeHandler *cCwCharacterWrapper::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cCwCharacterWrapper(pPrototype);
        return 0;
    }

    Fun_Runtime::cClass &cCwCharacterWrapper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwCharacterWrapperClass = new Fun_Runtime::cClass(0x673, "cCwCharacterWrapper", 0x41C0);
        return *cCwCharacterWrapperClass;
    }

    const Fun_Runtime::cClass *cCwCharacterWrapper::ms_pcCwCharacterWrapperClass = &cCwCharacterWrapper::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cCwCharacterWrapperRegistrar(
        "cCwCharacterWrapper", cCwCharacterWrapper::MakeNew, 0x41C0, false);

    // CD2 0x82FACE80: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCwCharacterWrappercCwCharacterInheritRegistrar(
        CHARACTER::cCwCharacterWrapper::StaticCreateClass(), CHARACTER::cCwCharacter::StaticCreateClass());

    // CD2 0x82FACF38: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCwCharacterWrapperSpawningRegistrar(
        cCwCharacterWrapper::StaticCreateClass(), cCwCharacterWrapper::SpawnFromPrototype);
}
