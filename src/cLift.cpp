// src/cLift.cpp
//
// Class: cLift (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cLift.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPrismaticProp.h"
#include "rws/classfactory.h"
#include "unknown/cLift.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cLift::ms_pcLiftClass = &cLift::StaticCreateClass();

    Fun_Runtime::cClass &cLift::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cLiftClass = new Fun_Runtime::cClass(0x102B, "cLift", 0xF30);
        return *cLiftClass;
    }

    static RWS::CClassFactory::CRegistrar cLiftRegistrar(
        "cLift", cLift::MakeNew, 0xF30, false);

    // CD2 0x82FF7770: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cLiftcPrismaticPropInheritRegistrar(
        unknown::cLift::StaticCreateClass(), Prop::cPrismaticProp::StaticCreateClass());

    // CD2 0x82FF7828: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cLiftSpawningRegistrar(
        cLift::StaticCreateClass(), cLift::SpawnFromPrototype);

    const char *cLift::RetClassName() const
    {
        return "cLift";
    }

    const Fun_Runtime::cClass &cLift::RetClass() const
    {
        return *ms_pcLiftClass;
    }

    bool cLift::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcLiftClass->IsA(c);
    }

    RWS::CAttributeHandler *cLift::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cLift(prototype);
        return 0;
    }

    // CD2 0x82739178 has no derived cleanup beyond vtable restoration.
    cLift::~cLift()
    {
    }

    Fun_Runtime::RetVal cLift::cLiftPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
