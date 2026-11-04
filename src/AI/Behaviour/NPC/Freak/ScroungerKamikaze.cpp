#include "fun_runtime/inheritance_registrar.h"
#include "AI/Scrounger.h"
#include "AI/ScroungerKamikaze.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerKamikaze::ms_pScroungerKamikazeClass = &ScroungerKamikaze::StaticCreateClass();


    const Fun_Runtime::cClass &ScroungerKamikaze::RetClass() const
    {
        return *ms_pScroungerKamikazeClass;
    }

    const char *ScroungerKamikaze::RetClassName() const
    {
        return "ScroungerKamikaze";
    }

    bool ScroungerKamikaze::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pScroungerKamikazeClass->IsA(c);
    }

    RWS::CAttributeHandler *ScroungerKamikaze::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new ScroungerKamikaze();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar ScroungerKamikazeRegistrar(
        "ScroungerKamikaze", ScroungerKamikaze::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &ScroungerKamikaze::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerKamikazeClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "ScroungerKamikaze", 0x140);
        return *ScroungerKamikazeClass;
    }
}

// CD2 0x82F94748: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar ScroungerKamikazeScroungerInheritRegistrar(
        AI::ScroungerKamikaze::StaticCreateClass(), AI::Scrounger::StaticCreateClass());
}

#include <new>

// CD2 0x824BDDF0: placement factory; Scrounger's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *ScroungerKamikaze::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) ScroungerKamikaze;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F94800: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar ScroungerKamikazeSpawningRegistrar(
        ScroungerKamikaze::StaticCreateClass(), ScroungerKamikaze::SpawnFromPrototype);
}
