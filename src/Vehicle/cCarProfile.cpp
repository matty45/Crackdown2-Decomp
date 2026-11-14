// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Vehicle/cCarProfile.h"
#include "rws/classfactory.h"
#include "rws/msg.h"
#include "cd2/memory.h"

namespace Vehicle
{
    RWS::CAttributeHandler *cCarProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCarProfile;
    }

    const char *cCarProfile::RetClassName() const
    {
        return "cCarProfile";
    }

    cCarProfile::~cCarProfile()
    {
        UnRegisterMsg(m_Msg_Data_Modified);
    }

    void cCarProfile::HandleEvents(RWS::CMsg &msg)
    {
        if (msg.Id == m_Msg_Return_RB_Self)
            msg.pData = this;
    }

    static RWS::CClassFactory::CRegistrar cCarProfileRegistrar(
        "cCarProfile", cCarProfile::MakeNew, 0x8F0, false);
}
