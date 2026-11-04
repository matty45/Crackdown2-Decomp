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

#include "cd2/memory.h"

// CD2 0x82623E60: the class-factory constructor; the constructor stays out of line.
namespace Equip
{
    RWS::CAttributeHandler *cBulletData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBulletData;
    }
}
