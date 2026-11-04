#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cPickupBase.h"
#include "rws/classfactory.h"
// src/cAudioLog.cpp
//
// Class: cAudioLog (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAudioLog.obj.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cAudioLog.cpp

#include "unknown/cAudioLog.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cAudioLog::ms_pcAudioLogClass = &cAudioLog::StaticCreateClass();

    Fun_Runtime::cClass &cAudioLog::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAudioLogClass = new Fun_Runtime::cClass(0x115, "cAudioLog", 0x1A0);
        return *cAudioLogClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cAudioLogRegistrar(
        "cAudioLog", cAudioLog::MakeNew, 0x1A0, false);
}

// CD2 0x82FF10F0: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cAudioLogcPickupBaseInheritRegistrar(
        unknown::cAudioLog::StaticCreateClass(), PHYSICS::cPickupBase::StaticCreateClass());
}

namespace unknown
{
    const char *cAudioLog::RetClassName() const
    {
        return "cAudioLog";
    }
}

namespace unknown
{
    const Fun_Runtime::cClass &cAudioLog::RetClass() const
    {
        return *ms_pcAudioLogClass;
    }
}
