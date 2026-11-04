#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/EquipmentDropBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *EquipmentDropBehaviour::ms_pEquipmentDropBehaviourClass = &EquipmentDropBehaviour::StaticCreateClass();

    EquipmentDropBehaviour::EquipmentDropBehaviour() {}

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
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar EquipmentDropBehaviourRegistrar(
        "EquipmentDropBehaviour", EquipmentDropBehaviour::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &EquipmentDropBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *EquipmentDropBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "EquipmentDropBehaviour", 0x140);
        return *EquipmentDropBehaviourClass;
    }
}

// CD2 0x82F9B948: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar EquipmentDropBehaviourcPilotBaseInheritRegistrar(
        AI::EquipmentDropBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

// CD2 0x82F9BA00: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar EquipmentDropBehaviourSpawningRegistrar(
        EquipmentDropBehaviour::StaticCreateClass(), EquipmentDropBehaviour::SpawnFromPrototype);
}
