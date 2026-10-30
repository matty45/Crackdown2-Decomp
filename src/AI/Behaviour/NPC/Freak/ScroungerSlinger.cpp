#include "AI/ScroungerSlinger.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerSlinger::ms_pScroungerSlingerClass = 0;

    ScroungerSlinger::ScroungerSlinger() {}

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

static RWS::CClassFactory::CRegistrar ScroungerSlingerRegistrar(
    "ScroungerSlinger", AI::ScroungerSlinger::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar ScroungerSlingerRegistrar(
        "ScroungerSlinger", ScroungerSlinger::MakeNew, 0x140, false);
}
