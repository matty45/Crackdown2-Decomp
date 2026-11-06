// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/cTrainingHeliPilot.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass *cTrainingHeliPilot::ms_pcTrainingHeliPilotClass = &cTrainingHeliPilot::StaticCreateClass();

    RWS::CAttributeHandler *cTrainingHeliPilot::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cTrainingHeliPilot;
        return 0;
    }

    const Fun_Runtime::cClass &cTrainingHeliPilot::RetClass() const
    {
        return *ms_pcTrainingHeliPilotClass;
    }

    const char *cTrainingHeliPilot::RetClassName() const
    {
        return "cTrainingHeliPilot";
    }

    bool cTrainingHeliPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingHeliPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingHeliPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingHeliPilot();
    }

    static RWS::CClassFactory::CRegistrar cTrainingHeliPilotRegistrar(
        "cTrainingHeliPilot", cTrainingHeliPilot::MakeNew, 0x150, false);

    Fun_Runtime::cClass &cTrainingHeliPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTrainingHeliPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cTrainingHeliPilot", 0x150);
        return *cTrainingHeliPilotClass;
    }

    // CD2 0x82F9CA28: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTrainingHeliPilotcPilotBaseInheritRegistrar(
        AI::cTrainingHeliPilot::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());

    // CD2 0x82F9CAE0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTrainingHeliPilotSpawningRegistrar(
        cTrainingHeliPilot::StaticCreateClass(), cTrainingHeliPilot::SpawnFromPrototype);
}
