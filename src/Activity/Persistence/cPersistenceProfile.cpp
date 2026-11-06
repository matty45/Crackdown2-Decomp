// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
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
