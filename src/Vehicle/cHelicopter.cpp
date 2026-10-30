#include "Vehicle/cHelicopter.h"
#include "rws/classfactory.h"

namespace Vehicle
{
    const char *cHelicopter::RetClassName() const
    {
        return "cHelicopter";
    }
}

namespace Vehicle
{
    static RWS::CClassFactory::CRegistrar cHelicopterRegistrar(
        "cHelicopter", cHelicopter::MakeNew, 0x2DB0, false);
}
