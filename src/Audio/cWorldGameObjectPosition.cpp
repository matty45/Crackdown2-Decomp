#include "Audio/cWorldGameObjectPosition.h"
#include "rws/classfactory.h"

namespace Audio
{
    const Fun_Runtime::cClass *cWorldGameObjectPosition::ms_pcWorldGameObjectPositionClass = 0;

    cWorldGameObjectPosition::cWorldGameObjectPosition() {}

    const Fun_Runtime::cClass &cWorldGameObjectPosition::RetClass() const
    {
        return *ms_pcWorldGameObjectPositionClass;
    }

    const char *cWorldGameObjectPosition::RetClassName() const
    {
        return "cWorldGameObjectPosition";
    }

    bool cWorldGameObjectPosition::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcWorldGameObjectPositionClass->IsA(c);
    }

    RWS::CAttributeHandler *cWorldGameObjectPosition::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWorldGameObjectPosition();
    }
}

static RWS::CClassFactory::CRegistrar cWorldGameObjectPositionRegistrar(
    "cWorldGameObjectPosition", Audio::cWorldGameObjectPosition::MakeNew, 0x7C, false);
