#include "fun_runtime/inheritance_registrar.h"
#include "Vehicle/cHelicopter.h"
#include "rws/classfactory.h"
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

#include "unknown/cWeaponisedHelicopter.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cWeaponisedHelicopter::ms_pcWeaponisedHelicopterClass = &cWeaponisedHelicopter::StaticCreateClass();

    Fun_Runtime::cClass &cWeaponisedHelicopter::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponisedHelicopterClass = new Fun_Runtime::cClass(0x4C70, "cWeaponisedHelicopter", 0x2DB0);
        return *cWeaponisedHelicopterClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cWeaponisedHelicopterRegistrar(
        "cWeaponisedHelicopter", cWeaponisedHelicopter::MakeNew, 0x2DB0, false);
}

// CD2 0x82FEA498: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cWeaponisedHelicoptercHelicopterInheritRegistrar(
        unknown::cWeaponisedHelicopter::StaticCreateClass(), Vehicle::cHelicopter::StaticCreateClass());
}
