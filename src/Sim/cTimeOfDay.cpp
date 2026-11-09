// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/script_type_registrar.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/scripthost.h"
#include "rws/classfactory.h"
#include "Sim/cTimeOfDay.h"
#include "Sim/cTODNotification.h"
#include "AI/cTimePeriodChangedEvent.h"
#include "AI/cTODDawnEvent.h"
#include "AI/cTODDuskEvent.h"
#include "cd2/memory.h"

namespace Sim
{
    RWS::CAttributeHandler *cTimeOfDay::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTimeOfDay;
    }

    const char *cTimeOfDay::RetClassName() const
    {
        return "cTimeOfDay";
    }

    const Fun_Runtime::cScriptTypeRegistration *cTimeOfDay::RetScriptTypeRegistration() const
    {
        return &g_cTimeOfDay;
    }
}

// Event getters occupy the addresses between cTimeOfDay's metadata getter and its class descriptor.
namespace AI
{
    const Fun_Runtime::cScriptTypeRegistration *cTODDuskEvent::RetScriptTypeRegistration() const
    {
        return &g_cTODDuskEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cTODDawnEvent::RetScriptTypeRegistration() const
    {
        return &g_cTODDawnEvent;
    }

    const Fun_Runtime::cScriptTypeRegistration *cTimePeriodChangedEvent::RetScriptTypeRegistration() const
    {
        return &g_cTimePeriodChangedEvent;
    }
}

namespace Sim
{

    Fun_Runtime::cClass &cTODNotification::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTODNotificationClass = new Fun_Runtime::cClass(0x3FA, "cTODNotification", 0x1C);
        return *cTODNotificationClass;
    }

    Fun_Runtime::cClass &cTimeOfDay::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTimeOfDayClass = new Fun_Runtime::cClass(0x3F9, "cTimeOfDay", 0x2B0);
        return *cTimeOfDayClass;
    }

    void TODForceUpdatePhase(void *, wchar_t *)
    {
        cTimeOfDay *timeOfDay = cTimeOfDay::ms_pInstance;
        if (timeOfDay && timeOfDay->RetNetRole() == eNR_Authority)
            timeOfDay->SetForceUpdatePhaseStep(!timeOfDay->RetForceUpdatePhaseStep());
    }

    const Fun_Runtime::cClass *cTODNotification::ms_pcTODNotificationClass = &cTODNotification::StaticCreateClass();

    // CD2 0x83002028: script metadata parent, distinct from the four-byte C++ registered-class base.
    static Fun_Runtime::cInheritanceRegistrar cTODNotificationcScriptHostInheritRegistrar(
        cTODNotification::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    const Fun_Runtime::cClass *cTimeOfDay::ms_pcTimeOfDayClass = &cTimeOfDay::StaticCreateClass();

    // CD2 0x830020B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTimeOfDaycScriptHostInheritRegistrar(
        Sim::cTimeOfDay::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    // CD2 0x83002120: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTimeOfDaycDebugPageHandlerInheritRegistrar(
        Sim::cTimeOfDay::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTimeOfDayRegistrar(
        "cTimeOfDay", cTimeOfDay::MakeNew, 0x2B0, false);
}

Fun_Runtime::cScriptTypeRegistrar<Sim::cTimeOfDay> g_cTimeOfDay("cTimeOfDay", "cScriptHost"); // global at 0x838518A0
