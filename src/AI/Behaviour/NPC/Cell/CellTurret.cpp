#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellTurret.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *CellTurret::ms_pCellTurretClass = &CellTurret::StaticCreateClass();

    CellTurret::CellTurret() {}

    const Fun_Runtime::cClass &CellTurret::RetClass() const
    {
        return *ms_pCellTurretClass;
    }

    const char *CellTurret::RetClassName() const
    {
        return "CellTurret";
    }

    bool CellTurret::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellTurretClass->IsA(c);
    }

}

namespace AI
{
    static RWS::CClassFactory::CRegistrar CellTurretRegistrar(
        "CellTurret", CellTurret::MakeNew, 0x100, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &CellTurret::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellTurretClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellTurret", 0x100);
        return *CellTurretClass;
    }
}

// CD2 0x82F96778: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar CellTurretNPCArmedBehaviourInheritRegistrar(
        AI::CellTurret::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());
}

// CD2 0x824C51B8: the class factory builds the prototype.
namespace AI
{
    RWS::CAttributeHandler *CellTurret::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellTurretPrototype(packet);
    }
}
