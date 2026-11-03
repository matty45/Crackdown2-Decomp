#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/cOutlines2.cpp
//
// Class: cOutlines2 (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cOutlines2.cpp

#include "unknown/cOutlines2.h"
#include "cd2/memory.h"

namespace unknown
{
    RWS::CAttributeHandler *cOutlines2::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cOutlines2;
    }

    const char *cOutlines2::RetClassName() const
    {
        return "cOutlines2";
    }

    const Fun_Runtime::cClass &cOutlines2::RetClass() const
    {
        return *ms_pcOutlines2Class;
    }

    bool cOutlines2::IsA(const Fun_Runtime::cClass &test) const
    {
        return ms_pcOutlines2Class->IsA(test);
    }

    const Fun_Runtime::cClass *cOutlines2::ms_pcOutlines2Class = &cOutlines2::StaticCreateClass();

    Fun_Runtime::cClass &cOutlines2::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cOutlines2Class = new Fun_Runtime::cClass(0x1027FB, "cOutlines2", 0x7C);
        return *cOutlines2Class;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cOutlines2Registrar(
        "cOutlines2", cOutlines2::MakeNew, 0x7C, false);
}

// CD2 0x83007900: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cOutlines2cNonGameBaseInheritRegistrar(
        unknown::cOutlines2::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}
