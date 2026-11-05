#include "rws/classfactory.h"
// src/cStaticInterestingObject.cpp
//
// Class: cStaticInterestingObject (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cStaticInterestingObject.cpp

#include "unknown/cStaticInterestingObject.h"
#include "fun_runtime/inheritance_registrar.h"

namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cStaticInterestingObjectcInterestingObjectInheritRegistrar(
        cStaticInterestingObject::StaticCreateClass(), cInterestingObject::StaticCreateClass());
}
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    static Fun_Runtime::cScriptTypeRegistrar<cStaticInterestingObject> cStaticInterestingObjectScriptRegistrar(
        "cStaticInterestingObject", "cInterestingObject");
}

namespace unknown
{
    const Fun_Runtime::cClass *cStaticInterestingObject::ms_pcStaticInterestingObjectClass = &cStaticInterestingObject::StaticCreateClass();

    Fun_Runtime::cClass &cStaticInterestingObject::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStaticInterestingObjectClass = new Fun_Runtime::cClass(0x3EB, "cStaticInterestingObject", 0xC0);
        return *cStaticInterestingObjectClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cStaticInterestingObjectRegistrar(
        "cStaticInterestingObject", cStaticInterestingObject::MakeNew, 0xC0, false);
}

namespace unknown
{
    const Fun_Runtime::cClass &cStaticInterestingObject::RetClass() const
    {
        return *ms_pcStaticInterestingObjectClass;
    }
}

namespace unknown
{
    const Fun_Runtime::cScriptTypeRegistration *cStaticInterestingObject::RetScriptTypeRegistration() const
    {
        return &cStaticInterestingObjectScriptRegistrar;
    }
}
