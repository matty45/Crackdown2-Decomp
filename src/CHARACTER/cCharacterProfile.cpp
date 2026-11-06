#include "fun_runtime/retval.h"
#include "CHARACTER/cCharacterProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rws/msg.h"

namespace CHARACTER
{
    const char *cCharacterProfile::RetClassName() const
    {
        return "cCharacterProfile";
    }

    static RWS::CClassFactory::CRegistrar cCharacterProfileRegistrar(
        "cCharacterProfile", cCharacterProfile::MakeNew, 0x260, false);

    Fun_Runtime::RetVal cCharacterProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cCharacterProfile::HandleEvents(RWS::CMsg &msg)
    {
        if (msg.Id == m_Msg_Return_Self)
            msg.pData = this;
    }

    // CD2 0x82553190: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCharacterProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCharacterProfile;
    }
}
