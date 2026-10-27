#include "AI/cHeliCallZone.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cHeliCallZone::ms_pcHeliCallZoneClass = 0;

    cHeliCallZone::cHeliCallZone() {}

    const Fun_Runtime::cClass &cHeliCallZone::RetClass() const
    {
        return *ms_pcHeliCallZoneClass;
    }

    const char *cHeliCallZone::RetClassName() const
    {
        return "cHeliCallZone";
    }

    bool cHeliCallZone::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcHeliCallZoneClass->IsA(c);
    }

    RWS::CAttributeHandler *cHeliCallZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHeliCallZone();
    }
}

static RWS::CClassFactory::CRegistrar cHeliCallZoneRegistrar(
    "cHeliCallZone", AI::cHeliCallZone::MakeNew, 0x7C, false);
