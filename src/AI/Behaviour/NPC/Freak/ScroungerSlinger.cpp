#include "fun_runtime/inheritance_registrar.h"
#include "AI/Scrounger.h"
#include "AI/ScroungerSlinger.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerSlinger::ms_pScroungerSlingerClass = &ScroungerSlinger::StaticCreateClass();


    const Fun_Runtime::cClass &ScroungerSlinger::RetClass() const
    {
        return *ms_pScroungerSlingerClass;
    }

    const char *ScroungerSlinger::RetClassName() const
    {
        return "ScroungerSlinger";
    }

    bool ScroungerSlinger::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pScroungerSlingerClass->IsA(c);
    }

    RWS::CAttributeHandler *ScroungerSlinger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new ScroungerSlinger();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar ScroungerSlingerRegistrar(
        "ScroungerSlinger", ScroungerSlinger::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &ScroungerSlinger::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerSlingerClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "ScroungerSlinger", 0x140);
        return *ScroungerSlingerClass;
    }
}

// CD2 0x82F94B80: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar ScroungerSlingerScroungerInheritRegistrar(
        AI::ScroungerSlinger::StaticCreateClass(), AI::Scrounger::StaticCreateClass());
}

#include <new>

// CD2 0x824BE608: placement factory; Scrounger's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *ScroungerSlinger::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) ScroungerSlinger;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F94C38: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar ScroungerSlingerSpawningRegistrar(
        ScroungerSlinger::StaticCreateClass(), ScroungerSlinger::SpawnFromPrototype);
}
