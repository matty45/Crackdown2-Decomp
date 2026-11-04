#include "rws/classfactory.h"
// src/cTransformingCar.cpp
//
// Class: cTransformingCar (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cTransformingCar.cpp

#include "unknown/cTransformingCar.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cTransformingCar::ms_pcTransformingCarClass = &cTransformingCar::StaticCreateClass();

    Fun_Runtime::cClass &cTransformingCar::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTransformingCarClass = new Fun_Runtime::cClass(0x14, "cTransformingCar", 0x67D0);
        return *cTransformingCarClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cTransformingCarRegistrar(
        "cTransformingCar", cTransformingCar::MakeNew, 0x67D0, false);
}

// CD2 0x826AB518.
namespace unknown
{
    const char *cTransformingCar::RetClassName() const
    {
        return "cTransformingCar";
    }
}

#include "fun_runtime/inheritance_registrar.h"
#include "Vehicle/cCar.h"

// CD2 0x82FE7100: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cTransformingCarcCarInheritRegistrar(
        unknown::cTransformingCar::StaticCreateClass(), Vehicle::cCar::StaticCreateClass());
}

#include "unknown/cTransforming.h"

// CD2 0x82FE7168: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cTransformingCarcTransformingInheritRegistrar(
        unknown::cTransformingCar::StaticCreateClass(), unknown::cTransforming::StaticCreateClass());
}
