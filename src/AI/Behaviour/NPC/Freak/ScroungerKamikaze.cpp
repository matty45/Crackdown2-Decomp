#include "AI/ScroungerKamikaze.h"
#include "rws/classfactory.h"

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
