// src/cAgencyATV.cpp
//
// Class: cAgencyATV (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAgencyATV.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "unknown/cAgencyATV.h"
#include "cd2/memory.h"
#include "unknown/cAgencyATVPrototype.h"
#include "Vehicle/cAgencyCar.h"
#include "fun_runtime/inheritance_registrar.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAgencyATV::ms_pcAgencyATVClass = &cAgencyATV::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyATV::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyATVClass = new Fun_Runtime::cClass(0x12065, "cAgencyATV", 0x31F0);
        return *cAgencyATVClass;
    }

    // CD2 0x82FEAC70: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyATVcAgencyCarInheritRegistrar(
        unknown::cAgencyATV::StaticCreateClass(), Vehicle::cAgencyCar::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAgencyATVRegistrar(
        "cAgencyATV", cAgencyATV::MakeNew, 0x31F0, false);

    // CD2 0x82FEAD28: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyATVSpawningRegistrar(
        cAgencyATV::StaticCreateClass(), cAgencyATV::SpawnFromPrototype);

    RWS::CAttributeHandler *cAgencyATV::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyATVPrototype(packet);
    }

    const char *cAgencyATV::RetClassName() const
    {
        return "cAgencyATV";
    }

    RWS::CAttributeHandler *cAgencyATV::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAgencyATV;
        return 0;
    }

    const Fun_Runtime::cClass &cAgencyATV::RetClass() const
    {
        return *ms_pcAgencyATVClass;
    }

    Fun_Runtime::RetVal cAgencyATVPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
