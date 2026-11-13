// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "GameManagement/cGameModeVFXProfile.h"
#include "cd2/memory.h"
#include "VFX/cParticleEffectManager.h"
#include "rw/rwmem.h"

namespace GameManagement
{
    int cGameModeVFXProfile::m_aVFXID[13];
    float cGameModeVFXProfile::m_fMaxHeightScale;

    RWS::CAttributeHandler *cGameModeVFXProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGameModeVFXProfile(packet);
    }

    const char *cGameModeVFXProfile::RetClassName() const
    {
        return "cGameModeVFXProfile";
    }

    void cGameModeVFXProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        RWS::CAttributeHandler::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cGameModeVFXProfile"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_RoofVFX_Start:
                m_aVFXID[0] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoofVFX_LOD1:
                m_aVFXID[1] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoofVFX_LOD2:
                m_aVFXID[2] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoofVFX_End:
                m_aVFXID[3] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoofVFX_PassThrough:
                m_aVFXID[4] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoadVFX_Start:
                m_aVFXID[5] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoadVFX_LOD1:
                m_aVFXID[6] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoadVFX_LOD2:
                m_aVFXID[7] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoadVFX_End:
                m_aVFXID[8] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_RoadVFX_PassThrough:
                m_aVFXID[9] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_TagVFX_Start:
                m_aVFXID[10] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_TagVFX_Orb:
                m_aVFXID[11] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_TagVFX_OrbTrail:
                m_aVFXID[12] = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            case CMD_Max_VFX_HeightScale:
                {
                    float heightScale = it->GetAs_float();
                    RwMemNative32(&heightScale, sizeof(heightScale));
                    m_fMaxHeightScale = heightScale;
                }
                break;
            }
        }
    }

    static RWS::CClassFactory::CRegistrar cGameModeVFXProfileRegistrar(
        "cGameModeVFXProfile", cGameModeVFXProfile::MakeNew, 0x18, false);
}
