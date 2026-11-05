#include "fun_runtime/script_type_registrar.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/scripthost.h"
#include "rws/classfactory.h"
#include "Sim/cTimeOfDay.h"
#include "cd2/memory.h"

Fun_Runtime::cScriptTypeRegistrar<Sim::cTimeOfDay> g_cTimeOfDay("cTimeOfDay", "cScriptHost");     // global at 0x838518A0
unsigned char g_AIE_TODDUSK;     // global at 0x83851758
unsigned char g_AIE_TODDAWN;     // global at 0x8385177C
unsigned char g_AIE_TIME_PERIOD_CHANGED;     // global at 0x838517A0

namespace Sim
{
    void *cTimeOfDay::GetPtrcTimeOfDay() const
    {
        return &g_cTimeOfDay;
    }

    void *cTimeOfDay::GetPtrAIE_TODDUSK() const
    {
        return &g_AIE_TODDUSK;
    }

    void *cTimeOfDay::GetPtrAIE_TODDAWN() const
    {
        return &g_AIE_TODDAWN;
    }

    void *cTimeOfDay::GetPtrAIE_TIME_PERIOD_CHANGED() const
    {
        return &g_AIE_TIME_PERIOD_CHANGED;
    }

    Fun_Runtime::cClass &cTimeOfDay::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTimeOfDayClass = new Fun_Runtime::cClass(0x3F9, "cTimeOfDay", 0x2B0);
        return *cTimeOfDayClass;
    }

    const Fun_Runtime::cClass *cTimeOfDay::ms_pcTimeOfDayClass = &cTimeOfDay::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cTimeOfDayRegistrar(
        "cTimeOfDay", cTimeOfDay::MakeNew, 0x2B0, false);

    // CD2 0x830020B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTimeOfDaycScriptHostInheritRegistrar(
        Sim::cTimeOfDay::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    // CD2 0x83002120: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTimeOfDaycDebugPageHandlerInheritRegistrar(
        Sim::cTimeOfDay::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
