#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/EquipmentDropBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass *EquipmentDropBehaviour::ms_pEquipmentDropBehaviourClass = &EquipmentDropBehaviour::StaticCreateClass();

    RWS::CAttributeHandler *EquipmentDropBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) EquipmentDropBehaviour;
        return 0;
    }

    const Fun_Runtime::cClass &EquipmentDropBehaviour::RetClass() const
    {
        return *ms_pEquipmentDropBehaviourClass;
    }

    const char *EquipmentDropBehaviour::RetClassName() const
    {
        return "EquipmentDropBehaviour";
    }

    bool EquipmentDropBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pEquipmentDropBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *EquipmentDropBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new EquipmentDropBehaviour();
    }

    static RWS::CClassFactory::CRegistrar EquipmentDropBehaviourRegistrar(
        "EquipmentDropBehaviour", EquipmentDropBehaviour::MakeNew, 0x140, false);

    Fun_Runtime::cClass &EquipmentDropBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *EquipmentDropBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "EquipmentDropBehaviour", 0x140);
        return *EquipmentDropBehaviourClass;
    }

    // CD2 0x82F9B948: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar EquipmentDropBehaviourcPilotBaseInheritRegistrar(
        AI::EquipmentDropBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());

    // CD2 0x82F9BA00: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar EquipmentDropBehaviourSpawningRegistrar(
        EquipmentDropBehaviour::StaticCreateClass(), EquipmentDropBehaviour::SpawnFromPrototype);
}
