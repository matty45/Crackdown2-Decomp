#include "AI/ScroungerKamikaze.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerKamikaze::ms_pScroungerKamikazeClass = 0;

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

static RWS::CClassFactory::CRegistrar ScroungerKamikazeRegistrar(
    "ScroungerKamikaze", AI::ScroungerKamikaze::MakeNew, 0x7C, false);
