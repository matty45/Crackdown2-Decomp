#include "AI/Reaper.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Reaper::ms_pReaperClass = 0;

    Reaper::Reaper() {}

    const Fun_Runtime::cClass &Reaper::RetClass() const
    {
        return *ms_pReaperClass;
    }

    const char *Reaper::RetClassName() const
    {
        return "Reaper";
    }

    bool Reaper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pReaperClass->IsA(c);
    }

    RWS::CAttributeHandler *Reaper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new Reaper();
    }
}

static RWS::CClassFactory::CRegistrar ReaperRegistrar(
    "Reaper", AI::Reaper::MakeNew, 0x7C, false);
