#include "Activity/cPersistenceProfile.h"
#include "rws/classfactory.h"

namespace Activity
{
    const char *cPersistenceProfile::RetClassName() const
    {
        return "cPersistenceProfile";
    }

    RWS::CAttributeHandler *cPersistenceProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cPersistenceProfile *p = new cPersistenceProfile();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cPersistenceProfileRegistrar(
        "cPersistenceProfile", cPersistenceProfile::MakeNew, 0x18, false);
}
