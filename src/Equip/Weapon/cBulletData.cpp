// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Equip/cBulletData.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rws/msg.h"

namespace Equip
{
    const char *cBulletData::RetClassName() const
    {
        return "cBulletData";
    }

    void cBulletData::HandleEvents(RWS::CMsg &msg)
    {
        if (msg.Id == m_RetreveEventID)
            msg.pData = this;
    }

    static RWS::CClassFactory::CRegistrar cBulletDataRegistrar(
        "cBulletData", cBulletData::MakeNew, 0x138, false);

    // CD2 0x82623E60: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cBulletData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBulletData;
    }
}
