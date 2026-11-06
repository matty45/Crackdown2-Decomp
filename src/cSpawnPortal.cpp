// src/cSpawnPortal.cpp
//
// Class: cSpawnPortal (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cSpawnPortal.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include "rws/classfactory.h"
#include "unknown/cSpawnPortal.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cSpawnPortal::ms_pcSpawnPortalClass = &cSpawnPortal::StaticCreateClass();

    Fun_Runtime::cClass &cSpawnPortal::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSpawnPortalClass = new Fun_Runtime::cClass(0x1025, "cSpawnPortal", 0xEC0);
        return *cSpawnPortalClass;
    }

    static RWS::CClassFactory::CRegistrar cSpawnPortalRegistrar(
        "cSpawnPortal", cSpawnPortal::MakeNew, 0xEC0, false);

    // CD2 0x82FF8C10: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSpawnPortalcHingedPropInheritRegistrar(
        unknown::cSpawnPortal::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());

    // CD2 0x82FF8CC8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cSpawnPortalSpawningRegistrar(
        cSpawnPortal::StaticCreateClass(), cSpawnPortal::SpawnFromPrototype);

    RWS::CAttributeHandler *cSpawnPortal::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSpawnPortalPrototype(packet);
    }

    const char *cSpawnPortal::RetClassName() const
    {
        return "cSpawnPortal";
    }

    const Fun_Runtime::cClass &cSpawnPortal::RetClass() const
    {
        return *ms_pcSpawnPortalClass;
    }

    bool cSpawnPortal::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSpawnPortalClass->IsA(c);
    }

    // CD2 0x8273E238 has no derived cleanup beyond vtable restoration.
    cSpawnPortal::~cSpawnPortal()
    {
    }

    Fun_Runtime::RetVal cSpawnPortal::cSpawnPortalPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
