#include "AI/cAnimParams.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAnimParams::ms_pcAnimParamsClass = 0;

    cAnimParams::cAnimParams() {}

    const Fun_Runtime::cClass &cAnimParams::RetClass() const
    {
        return *ms_pcAnimParamsClass;
    }

    const char *cAnimParams::RetClassName() const
    {
        return "cAnimParams";
    }

    bool cAnimParams::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAnimParamsClass->IsA(c);
    }

    RWS::CAttributeHandler *cAnimParams::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAnimParams();
    }
}

static RWS::CClassFactory::CRegistrar cAnimParamsRegistrar(
    "cAnimParams", AI::cAnimParams::MakeNew, 0x7C, false);
