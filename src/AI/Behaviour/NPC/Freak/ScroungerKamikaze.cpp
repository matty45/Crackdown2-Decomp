#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/Scrounger.h"
#include "AI/ScroungerKamikaze.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerKamikaze::ms_pScroungerKamikazeClass = &ScroungerKamikaze::StaticCreateClass();

    ScroungerKamikaze::ScroungerKamikaze() {}

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

    static RWS::CClassFactory::CRegistrar ScroungerKamikazeRegistrar(
        "ScroungerKamikaze", ScroungerKamikaze::MakeNew, 0x140, false);

    Fun_Runtime::cClass &ScroungerKamikaze::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerKamikazeClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "ScroungerKamikaze", 0x140);
        return *ScroungerKamikazeClass;
    }

    // CD2 0x82F94748: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar ScroungerKamikazeScroungerInheritRegistrar(
        AI::ScroungerKamikaze::StaticCreateClass(), AI::Scrounger::StaticCreateClass());

    // CD2 0x82F94800: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar ScroungerKamikazeSpawningRegistrar(
        ScroungerKamikaze::StaticCreateClass(), ScroungerKamikaze::SpawnFromPrototype);
}
