// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Vehicle/cEightWheelerProfile.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cEightWheelerProfile::RetClassName() const
    {
        return "cEightWheelerProfile";
    }

    cEightWheelerProfile::~cEightWheelerProfile()
    {
        UnRegisterMsg(m_Msg_Data_Modified);
    }

    static RWS::CClassFactory::CRegistrar cEightWheelerProfileRegistrar(
        "cEightWheelerProfile", cEightWheelerProfile::MakeNew, 0x8F0, false);
}
