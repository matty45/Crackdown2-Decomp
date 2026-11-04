#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "AI/Squad.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *Squad::RetClassName() const
    {
        return "Squad";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar SquadRegistrar(
        "Squad", Squad::MakeNew, 0x390, false);
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &Squad::StaticCreateClass()
    {
        static Fun_Runtime::cClass *SquadClass = new Fun_Runtime::cClass(0x6A597, "Squad", 0x390);
        return *SquadClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *Squad::ms_pSquadClass = &Squad::StaticCreateClass();

    const Fun_Runtime::cClass &Squad::RetClass() const
    {
        return *ms_pSquadClass;
    }
}

namespace AI
{
    bool Squad::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pSquadClass->IsA(c);
    }
}

// CD2 0x82F9D298: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar SquadcNonGameBaseInheritRegistrar(
        AI::Squad::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x82F9D350: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar SquadSpawningRegistrar(
        Squad::StaticCreateClass(), Squad::SpawnFromPrototype);
}

namespace AI
{
    RWS::CAttributeHandler *Squad::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Squad;
        return 0;
    }
}
