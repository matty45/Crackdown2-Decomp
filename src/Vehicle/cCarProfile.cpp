#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "Vehicle/cCarProfile.h"
#include "rws/classfactory.h"
#include "rws/msg.h"

namespace Vehicle
{
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
