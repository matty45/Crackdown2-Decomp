#include "AI/ScroungerSlinger.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *ScroungerSlinger::ms_pScroungerSlingerClass = &ScroungerSlinger::StaticCreateClass();

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
