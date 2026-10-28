#include "Demo/cDemoSettings.h"
#include "rws/classfactory.h"

namespace Demo
{
    const char *cDemoSettings::RetClassName() const
    {
        return "cDemoSettings";
    }

    RWS::CAttributeHandler *cDemoSettings::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cDemoSettings *p = new cDemoSettings();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cDemoSettingsRegistrar(
        "cDemoSettings", cDemoSettings::MakeNew, 0x18, false);
}
