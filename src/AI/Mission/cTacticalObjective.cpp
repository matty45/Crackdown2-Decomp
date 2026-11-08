// AI/Mission/cTacticalObjective.cpp: RuffKing's Libraries/Shared/AI/Mission/cTacticalObjective.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "AI/cHeliDropPoint.h"
#include "AI/cTacticalObjective.h"
#include "cd2/memory.h"

namespace AI
{
    static RWS::CClassFactory::CRegistrar cHeliDropPointRegistrar(
        "cHeliDropPoint", cHeliDropPoint::MakeNew, 0x80, false);

    Fun_Runtime::cClass &cTacticalObjective::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTacticalObjectiveClass = new Fun_Runtime::cClass(0x9F3D5, "cTacticalObjective", 0x530);
        return *cTacticalObjectiveClass;
    }

    const Fun_Runtime::cClass *cTacticalObjective::ms_pcTacticalObjectiveClass = &cTacticalObjective::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cTacticalObjectivecMissionInheritRegistrar(
        cTacticalObjective::StaticCreateClass(), cMission::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cTacticalObjectiveRegistrar(
        "cTacticalObjective", cTacticalObjective::MakeNew, 0x530, false);
}
