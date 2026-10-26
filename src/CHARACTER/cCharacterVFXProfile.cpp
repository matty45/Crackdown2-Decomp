#include "CHARACTER/cCharacterVFXProfile.h"
#include "cd2/memory.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *const cCharacterVFXProfile::pcCharacterVFXProfileClassID = "cCharacterVFXProfile";

    cCharacterVFXProfile::cCharacterVFXProfile(const RWS::CAttributePacket &packet)
    {
        m_EventHandler.Register(this, packet.GetInstanceId());
    }

    const char *cCharacterVFXProfile::RetClassName() const
    {
        return pcCharacterVFXProfileClassID;
    }

    RWS::CAttributeHandler *cCharacterVFXProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCharacterVFXProfile(packet);
    }

    static RWS::CClassFactory::CRegistrar cCharacterVFXProfileRegistrar(
        "cCharacterVFXProfile", cCharacterVFXProfile::MakeNew, 0x130, false);
}
