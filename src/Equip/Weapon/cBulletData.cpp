#include "Equip/cBulletData.h"
#include "rws/classfactory.h"

namespace Equip
{
    const char *cBulletData::RetClassName() const
    {
        return "cBulletData";
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cBulletDataRegistrar(
        "cBulletData", cBulletData::MakeNew, 0x138, false);
}
