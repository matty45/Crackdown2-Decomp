#include "UI/cAgentColour.h"
#include "rws/classfactory.h"

namespace UI
{
    const char *cAgentColour::RetClassName() const
    {
        return "cAgentColour";
    }

    RWS::CAttributeHandler *cAgentColour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cAgentColour *p = new cAgentColour();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cAgentColourRegistrar(
        "cAgentColour", cAgentColour::MakeNew, 0x28, false);
}
