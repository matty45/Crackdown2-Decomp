// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cBreachHoleMission.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cBreachHoleMission::ms_pcBreachHoleMissionClass = &cBreachHoleMission::StaticCreateClass();

    cBreachHoleMission::cBreachHoleMission() {}

    const Fun_Runtime::cClass &cBreachHoleMission::RetClass() const
    {
        return *ms_pcBreachHoleMissionClass;
    }

    const char *cBreachHoleMission::RetClassName() const
    {
        return "cBreachHoleMission";
    }

    bool cBreachHoleMission::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcBreachHoleMissionClass->IsA(c);
    }

    RWS::CAttributeHandler *cBreachHoleMission::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cBreachHoleMission();
    }

    static RWS::CClassFactory::CRegistrar cBreachHoleMissionRegistrar(
        "cBreachHoleMission", cBreachHoleMission::MakeNew, 0x530, false);

    Fun_Runtime::cClass &cBreachHoleMission::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cBreachHoleMissionClass = new Fun_Runtime::cClass(0x9EFED, "cBreachHoleMission", 0x530);
        return *cBreachHoleMissionClass;
    }

    // CD2 0x82F89E38: runtime mission inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cBreachHoleMissioncMissionInheritRegistrar(
        AI::cBreachHoleMission::StaticCreateClass(), AI::cMission::StaticCreateClass());
}
