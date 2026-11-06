#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/retval.h"
#include "PHYSICS/cRigidBodyProfile.h"
#include "rws/classfactory.h"

namespace PHYSICS
{
    RWS::CAttributeHandler *cRigidBodyProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRigidBodyProfile;
    }

    const char *cRigidBodyProfile::RetClassName() const
    {
        return "cRigidBodyProfile";
    }

    cRigidBodyProfile::~cRigidBodyProfile()
    {
        UnLinkMsg(m_Msg_Return_RB_Self);
        UnRegisterMsg(m_Msg_Return_RB_Self);
    }

    static RWS::CClassFactory::CRegistrar cRigidBodyProfileRegistrar(
        "cRigidBodyProfile", cRigidBodyProfile::MakeNew, 0x300, false);

    Fun_Runtime::RetVal cRigidBodyProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
