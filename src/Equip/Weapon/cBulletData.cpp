#include "Equip/cBulletData.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Equip
{
    const char *cBulletData::RetClassName() const
    {
        return "cBulletData";
    }

    static RWS::CClassFactory::CRegistrar cBulletDataRegistrar(
        "cBulletData", cBulletData::MakeNew, 0x138, false);

    // CD2 0x82623E60: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cBulletData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBulletData;
    }
}
