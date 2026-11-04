#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "CHARACTER/cCwTransCharacter.h"
// src/cCwTransCharacterWrapper.cpp
//
// Class: cCwTransCharacterWrapper (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cCwTransCharacterWrapper.cpp

#include "CHARACTER/cCwTransCharacterWrapper.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    // CD2 0x82FAC1A0 registers the prototype factory 0x8253ED68 for this 0x5B40-byte character.
    static RWS::CClassFactory::CRegistrar cCwTransCharacterWrapperRegistrar(
        "cCwTransCharacterWrapper", cCwTransCharacterWrapper::MakeNew, 0x5B40, false);
}

#include "cd2/memory.h"

namespace CHARACTER
{
    Fun_Runtime::cClass &cCwTransCharacterWrapper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCwTransCharacterWrapperClass = new Fun_Runtime::cClass(0x672, "cCwTransCharacterWrapper", 0x5B40);
        return *cCwTransCharacterWrapperClass;
    }
}

namespace CHARACTER
{
    const Fun_Runtime::cClass *cCwTransCharacterWrapper::ms_pcCwTransCharacterWrapperClass = &cCwTransCharacterWrapper::StaticCreateClass();
}

// CD2 0x82FAC138: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cCwTransCharacterWrappercCwTransCharacterInheritRegistrar(
        CHARACTER::cCwTransCharacterWrapper::StaticCreateClass(), CHARACTER::cCwTransCharacter::StaticCreateClass());
}

// CD2 0x82FAC1F0: register the class descriptor and placement factory.
namespace CHARACTER
{
    static GOM::cProtoRegistrar cCwTransCharacterWrapperSpawningRegistrar(
        cCwTransCharacterWrapper::StaticCreateClass(), cCwTransCharacterWrapper::SpawnFromPrototype);
}

namespace CHARACTER
{
    const char *cCwTransCharacterWrapper::RetClassName() const
    {
        return "cCwTransCharacterWrapper";
    }
}

#include "CHARACTER/cCwTransCharacterWrapperPrototype.h"
#include "fun_runtime/retval.h"

namespace CHARACTER
{
    Fun_Runtime::RetVal cCwTransCharacterWrapperPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
