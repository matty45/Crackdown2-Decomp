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
