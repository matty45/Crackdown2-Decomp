#include "Billboard/BillboardData.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "Billboard/BillboardManager.h"

namespace Billboard
{
    void BillboardData::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, "BillboardData"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                m_pVideoResource = g_pBillboardManager->FindBillboardResource(it->GetAs_RWSGUID());
                break;
            case 1:
                m_strPlayEventName = it->GetAs_char_ptr();
                break;
            case 2:
                m_strStopEventName = it->GetAs_char_ptr();
                break;
            }
        }
        if (packet.IsInstanceCreationPacket())
            m_EventHandler.Register(this, packet.GetInstanceId());
    }

    BillboardData::~BillboardData()
    {
    }

    RWS::CAttributeHandler *BillboardData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new BillboardData;
    }

    static RWS::CClassFactory::CRegistrar BillboardDataRegistrar(
        "BillboardData", BillboardData::MakeNew, 0x68, false);

    const char *BillboardData::RetClassName() const
    {
        return "BillboardData";
    }
}
