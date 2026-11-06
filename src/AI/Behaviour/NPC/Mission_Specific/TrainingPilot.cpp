#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingPilot.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingPilot::ms_pTrainingPilotClass = &TrainingPilot::StaticCreateClass();

    RWS::CAttributeHandler *TrainingPilot::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) TrainingPilot;
        return 0;
    }

    const Fun_Runtime::cClass &TrainingPilot::RetClass() const
    {
        return *ms_pTrainingPilotClass;
    }

    const char *TrainingPilot::RetClassName() const
    {
        return "TrainingPilot";
    }

    bool TrainingPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingPilot();
    }
}

static RWS::CClassFactory::CRegistrar TrainingPilotRegistrar(
    "TrainingPilot", AI::TrainingPilot::MakeNew, 0xD0, false);

namespace AI
{
    Fun_Runtime::cClass &TrainingPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingPilot", 0xD0);
        return *TrainingPilotClass;
    }

    // CD2 0x82F98BF0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar TrainingPilotNPCBehaviourInheritRegistrar(
        AI::TrainingPilot::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F98CA8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar TrainingPilotSpawningRegistrar(
        TrainingPilot::StaticCreateClass(), TrainingPilot::SpawnFromPrototype);
}
