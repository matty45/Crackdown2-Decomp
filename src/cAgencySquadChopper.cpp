#include "fun_runtime/inheritance_registrar.h"
#include "VEHICLE_CONTROL/cHelicopterController.h"
#include "rws/classfactory.h"
// src/cAgencySquadChopper.cpp
//
// Class: cAgencySquadChopper (namespace: unknown). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAgencySquadChopper.cpp

#include "unknown/cAgencySquadChopper.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAgencySquadChopper::ms_pcAgencySquadChopperClass = &cAgencySquadChopper::StaticCreateClass();

    Fun_Runtime::cClass &cAgencySquadChopper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencySquadChopperClass = new Fun_Runtime::cClass(0x12066, "cAgencySquadChopper", 0x2360);
        return *cAgencySquadChopperClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cAgencySquadChopperRegistrar(
        "cAgencySquadChopper", cAgencySquadChopper::MakeNew, 0x2360, false);
}

// CD2 0x82FEBD00: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cAgencySquadChoppercVehicleInheritRegistrar(
        unknown::cAgencySquadChopper::StaticCreateClass(), Vehicle::cVehicle::StaticCreateClass());
}

// CD2 0x826EDB50.
namespace unknown
{
    const char *cAgencySquadChopper::RetClassName() const
    {
        return "cAgencySquadChopper";
    }
}
