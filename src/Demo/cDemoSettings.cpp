// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "Demo/cDemoSettings.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

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
