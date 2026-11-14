// src/cWeaponisedHelicopter.cpp
//
// Class: cWeaponisedHelicopter (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cWeaponisedHelicopter.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Vehicle/cHelicopter.h"
#include "rws/classfactory.h"
#include "unknown/cWeaponisedHelicopter.h"
#include "cd2/memory.h"
#include <new>

namespace unknown
{
    const Fun_Runtime::cClass *cWeaponisedHelicopter::ms_pcWeaponisedHelicopterClass = &cWeaponisedHelicopter::StaticCreateClass();

    RWS::CAttributeHandler *cWeaponisedHelicopter::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeaponisedHelicopter;
        return 0;
    }

    Fun_Runtime::cClass &cWeaponisedHelicopter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponisedHelicopterClass = new Fun_Runtime::cClass(0x4C70, "cWeaponisedHelicopter", 0x2DB0);
        return *cWeaponisedHelicopterClass;
    }

    cWeaponisedHelicopter::~cWeaponisedHelicopter()
    {
    }

    static RWS::CClassFactory::CRegistrar cWeaponisedHelicopterRegistrar(
        "cWeaponisedHelicopter", cWeaponisedHelicopter::MakeNew, 0x2DB0, false);

    // CD2 0x82FEA498: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cWeaponisedHelicoptercHelicopterInheritRegistrar(
        unknown::cWeaponisedHelicopter::StaticCreateClass(), Vehicle::cHelicopter::StaticCreateClass());

    // CD2 0x82FEA550: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cWeaponisedHelicopterSpawningRegistrar(
        cWeaponisedHelicopter::StaticCreateClass(), cWeaponisedHelicopter::SpawnFromPrototype);

    bool cWeaponisedHelicopter::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcWeaponisedHelicopterClass->IsA(c);
    }

    RWS::CAttributeHandler *cWeaponisedHelicopter::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponisedHelicopterPrototype(packet);
    }

    const char *cWeaponisedHelicopter::RetClassName() const
    {
        return "cWeaponisedHelicopter";
    }

    const Fun_Runtime::cClass &cWeaponisedHelicopter::RetClass() const
    {
        return *ms_pcWeaponisedHelicopterClass;
    }

    Fun_Runtime::RetVal cWeaponisedHelicopter::Term()
    {
        return cHelicopter::Term();
    }

    Fun_Runtime::RetVal cWeaponisedHelicopter::TermForReuse()
    {
        return cHelicopter::TermForReuse();
    }

    Fun_Runtime::RetVal cWeaponisedHelicopter::Slot37()
    {
        return cHelicopter::Slot37();
    }
}
