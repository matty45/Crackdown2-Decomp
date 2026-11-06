// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Vehicle/cSixWheelerProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cSixWheelerProfile::RetClassName() const
    {
        return "cSixWheelerProfile";
    }

    cSixWheelerProfile::~cSixWheelerProfile()
    {
        UnRegisterMsg(m_Msg_Data_Modified);
    }

    static RWS::CClassFactory::CRegistrar cSixWheelerProfileRegistrar(
        "cSixWheelerProfile", cSixWheelerProfile::MakeNew, 0x900, false);
}
