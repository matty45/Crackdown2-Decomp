// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cDocksMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const char *cDocksMission::RetClassName() const
    {
        return "cDocksMission";
    }

    static RWS::CClassFactory::CRegistrar cDocksMissionRegistrar(
        "cDocksMission", cDocksMission::MakeNew, 0x450, false);

    Fun_Runtime::cClass &cDocksMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cDocksMissionClass = new Fun_Runtime::cClass(0x9F4FE, "cDocksMission", 0x450);
        return *cDocksMissionClass;
    }

    const Fun_Runtime::cClass *cDocksMission::ms_pcDocksMissionClass = &cDocksMission::StaticCreateClass();

    const Fun_Runtime::cClass &cDocksMission::RetClass() const
    {
        return *ms_pcDocksMissionClass;
    }

    bool cDocksMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcDocksMissionClass->IsA(c);
    }

    // CD2 0x82F8A480: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cDocksMissioncMissionInheritRegistrar(
        AI::cDocksMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
