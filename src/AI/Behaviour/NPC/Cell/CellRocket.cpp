#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCArmedBehaviour.h"
#include "AI/CellRocket.h"
#include "AI/CellRocketPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *CellRocket::ms_pCellRocketClass = &CellRocket::StaticCreateClass();

    CellRocket::CellRocket() {}

    const Fun_Runtime::cClass &CellRocket::RetClass() const
    {
        return *ms_pCellRocketClass;
    }

    RWS::CAttributeHandler *CellRocket::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellRocketPrototype(packet);
    }

    const char *CellRocket::RetClassName() const
    {
        return "CellRocket";
    }

    bool CellRocket::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pCellRocketClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar CellRocketRegistrar(
        "CellRocket", CellRocket::MakeNew, 0x110, false);

    Fun_Runtime::cClass &CellRocket::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellRocketClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellRocket", 0x110);
        return *CellRocketClass;
    }

    // CD2 0x82F96340: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar CellRocketNPCArmedBehaviourInheritRegistrar(
        AI::CellRocket::StaticCreateClass(), AI::NPCArmedBehaviour::StaticCreateClass());

    // CD2 0x82F963F8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar CellRocketSpawningRegistrar(
        CellRocket::StaticCreateClass(), CellRocket::SpawnFromPrototype);
}
