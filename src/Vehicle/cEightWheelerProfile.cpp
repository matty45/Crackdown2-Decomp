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
