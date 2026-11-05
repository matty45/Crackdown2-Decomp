#include "rws/classfactory.h"
#include "unknown/cRenegadesProfile.h"

namespace unknown
{
    const char *cRenegadesProfile::RetClassName() const
    {
        return "cRenegadesProfile";
    }

    static RWS::CClassFactory::CRegistrar cRenegadesProfileRegistrar(
        "cRenegadesProfile", cRenegadesProfile::MakeNew, 0x40, false);
}
