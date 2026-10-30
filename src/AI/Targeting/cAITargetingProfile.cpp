// AI/Targeting/cAITargetingProfile.cpp: byte-exact against Crackdown 2 (title update), all 7 functions.
//   0x82451C60 MakeNew            0x82451CC8 constructor       0x82451CB8 RetClassName
//   0x82451DB8 scalar deleting destructor (compiler-generated, emitted here)
//   0x82451E18 HandleAttributes
//   0x82F841B8 / 0x8303AD80 dynamic initializer / at-exit destructor of cAITargetingProfileRegistrar
// The constructor zeroes m_TargetData with integer stores after building m_EventHandler: a memset in the body (value
// initialization in the initializer list zeroes it first; float assignments use stfs).
#include <string.h>
#include "AI/cAITargetingProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"

namespace AI
{
    const char *const cAITargetingProfile::pcAITargetingProfileClassID = "cAITargetingProfile";

    cAITargetingProfile::cAITargetingProfile(const RWS::CAttributePacket &attr)
    {
        memset(&m_TargetData, 0, sizeof(m_TargetData));
        m_EventHandler.Register(this, attr.GetInstanceId());
    }

    const char *cAITargetingProfile::RetClassName() const
    {
        return pcAITargetingProfileClassID;
    }

    void cAITargetingProfile::HandleAttributes(const RWS::CAttributePacket &attr)
    {
        for (RWS::CAttributeCommandIterator it(attr, pcAITargetingProfileClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_BasePoints:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_TargetData.m_fBasePoints = mem; }
                break;
            case CMD_Distance:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_TargetData.m_fDistancePoints = mem; }
                break;
            case CMD_Damage:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_TargetData.m_fDamagePoints = mem; }
                break;
            case CMD_Visibility:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_TargetData.m_fVisiblePoints = mem; }
                break;
            }
        }
    }

    RWS::CAttributeHandler *cAITargetingProfile::MakeNew(const RWS::CAttributePacket &attr, bool)
    {
        return new cAITargetingProfile(attr);
    }

    static RWS::CClassFactory::CRegistrar cAITargetingProfileRegistrar(
        "cAITargetingProfile", cAITargetingProfile::MakeNew, 0x3C, false);
}
