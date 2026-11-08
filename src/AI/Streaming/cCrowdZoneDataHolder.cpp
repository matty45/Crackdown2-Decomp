#include "AI/cCrowdZoneDataHolder.h"
// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "fun_runtime/inheritance_registrar.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass &cCrowdZoneDataHolder::RetClass() const
    {
        return *ms_pcCrowdZoneDataHolderClass;
    }

    RWS::CAttributeHandler *cCrowdZoneDataHolder::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCrowdZoneDataHolder;
    }

    const char *cCrowdZoneDataHolder::RetClassName() const
    {
        return "cCrowdZoneDataHolder";
    }

    const Fun_Runtime::cClass *cCrowdZoneDataHolder::ms_pcCrowdZoneDataHolderClass = &cCrowdZoneDataHolder::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cCrowdZoneDataHoldercNonGameBaseInheritRegistrar(
        cCrowdZoneDataHolder::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cCrowdZoneDataHolderRegistrar(
        "cCrowdZoneDataHolder", cCrowdZoneDataHolder::MakeNew, 0x7C, false);

    bool cCrowdZoneDataHolder::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcCrowdZoneDataHolderClass->IsA(testClass);
    }

    Fun_Runtime::cClass &cCrowdZoneDataHolder::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCrowdZoneDataHolderClass = new Fun_Runtime::cClass(0x445B, "cCrowdZoneDataHolder", 0x7C);
        return *cCrowdZoneDataHolderClass;
    }
}
