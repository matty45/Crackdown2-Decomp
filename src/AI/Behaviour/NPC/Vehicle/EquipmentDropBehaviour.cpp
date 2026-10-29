#include "AI/EquipmentDropBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *EquipmentDropBehaviour::ms_pEquipmentDropBehaviourClass = 0;

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

static RWS::CClassFactory::CRegistrar EquipmentDropBehaviourRegistrar(
    "EquipmentDropBehaviour", AI::EquipmentDropBehaviour::MakeNew, 0x7C, false);
