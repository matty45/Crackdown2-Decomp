// src/cAgencyGaragePlatform.cpp
//
// Class: cAgencyGaragePlatform (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAgencyGaragePlatform.cpp

#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPrismaticProp.h"
#include "rws/classfactory.h"
#include "unknown/cAgencyGaragePlatform.h"
#include "cd2/memory.h"
#include "unknown/cAgencyGaragePlatformPrototype.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAgencyGaragePlatform::ms_pcAgencyGaragePlatformClass = &cAgencyGaragePlatform::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyGaragePlatform::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyGaragePlatformClass = new Fun_Runtime::cClass(0x1024, "cAgencyGaragePlatform", 0xEE0);
        return *cAgencyGaragePlatformClass;
    }

    static RWS::CClassFactory::CRegistrar cAgencyGaragePlatformRegistrar(
        "cAgencyGaragePlatform", cAgencyGaragePlatform::MakeNew, 0xEE0, false);

    // CD2 0x82FF6BE8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyGaragePlatformcPrismaticPropInheritRegistrar(
        unknown::cAgencyGaragePlatform::StaticCreateClass(), Prop::cPrismaticProp::StaticCreateClass());

    // CD2 0x82FF6CA0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyGaragePlatformSpawningRegistrar(
        cAgencyGaragePlatform::StaticCreateClass(), cAgencyGaragePlatform::SpawnFromPrototype);

    const char *cAgencyGaragePlatform::RetClassName() const
    {
        return "cAgencyGaragePlatform";
    }

    // CD2 0x82736538 has no derived cleanup beyond vtable restoration.
    cAgencyGaragePlatform::~cAgencyGaragePlatform()
    {
    }

    Fun_Runtime::RetVal cAgencyGaragePlatformPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
