// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "unknown/cLaunchPadConfig.h"
#include "rws/classfactory.h"
#include "rw/rwmem.h"
#include "VFX/cParticleEffectManager.h"

namespace unknown
{
    // Initial values from CD2's static data, in declaration order.
    float cLaunchPadConfig::ms_fPadRadius = 3.0f;
    int cLaunchPadConfig::ms_nLaunchVFX = -1;
    int cLaunchPadConfig::ms_nTargetVFX = -1;
    int cLaunchPadConfig::ms_nTrailVFX = -1;
    float cLaunchPadConfig::ms_fVFXScale = 5.0f;
    float cLaunchPadConfig::ms_fTrailVFXScale = 1.0f;
    float cLaunchPadConfig::ms_fTrailVFXDelay = 1.0f;

    const char *cLaunchPadConfig::RetClassName() const
    {
        return "cLaunchPadConfig";
    }

    RWS::CAttributeHandler *cLaunchPadConfig::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cLaunchPadConfig *p = new cLaunchPadConfig();
        return p;
    }

    void cLaunchPadConfig::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, "cLaunchPadConfig"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_PadRadius:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    ms_fPadRadius = value;
                }
                break;
            case CMD_LaunchVFX:
                ms_nLaunchVFX = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_TargetVFX:
                ms_nTargetVFX = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_TrailVFX:
                ms_nTrailVFX = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_VFXScale:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    ms_fVFXScale = value;
                }
                break;
            case CMD_TrailVFXScale:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    ms_fTrailVFXScale = value;
                }
                break;
            case CMD_TrailVFXDelay:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    ms_fTrailVFXDelay = value;
                }
                break;
            }
        }
    }

    static RWS::CClassFactory::CRegistrar cLaunchPadConfigRegistrar(
        "cLaunchPadConfig", cLaunchPadConfig::MakeNew, 0x18, false);
}
