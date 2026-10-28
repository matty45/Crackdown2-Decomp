#include "RPG/cRPGGlobalsInterface.h"
#include "rws/classfactory.h"

namespace RPG
{
    const char *cRPGGlobalsInterface::RetClassName() const
    {
        return "cRPGGlobalsInterface";
    }

    RWS::CAttributeHandler *cRPGGlobalsInterface::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cRPGGlobalsInterface *p = new cRPGGlobalsInterface();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cRPGGlobalsInterfaceRegistrar(
        "cRPGGlobalsInterface", cRPGGlobalsInterface::MakeNew, 0x18, false);
}
