#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "AI/Squad.h"
#include "AI/SquadPrototype.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace AI
{
    RWS::CAttributeHandler *Squad::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new SquadPrototype(packet);
    }

    const char *Squad::RetClassName() const
    {
        return "Squad";
    }

    static RWS::CClassFactory::CRegistrar SquadRegistrar(
        "Squad", Squad::MakeNew, 0x390, false);

    Fun_Runtime::cClass &Squad::StaticCreateClass()
    {
        static Fun_Runtime::cClass *SquadClass = new Fun_Runtime::cClass(0x6A597, "Squad", 0x390);
        return *SquadClass;
    }

    const Fun_Runtime::cClass *Squad::ms_pSquadClass = &Squad::StaticCreateClass();

    const Fun_Runtime::cClass &Squad::RetClass() const
    {
        return *ms_pSquadClass;
    }

    bool Squad::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pSquadClass->IsA(c);
    }

    // CD2 0x82F9D298: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar SquadcNonGameBaseInheritRegistrar(
        AI::Squad::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x82F9D350: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar SquadSpawningRegistrar(
        Squad::StaticCreateClass(), Squad::SpawnFromPrototype);

    RWS::CAttributeHandler *Squad::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Squad;
        return 0;
    }
}
