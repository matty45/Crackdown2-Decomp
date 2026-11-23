// VFX/cBeaconExplosionEffect.cpp: RuffKing's Libraries/Shared/VFX/cBeaconExplosionEffect.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"

#include "VFX/cBeaconExplosionPassThroughShader.h"

namespace VFX
{
    cBeaconExplosionPassThroughShader *cBeaconExplosionPassThroughShader::ms_pInstance;

    bool cBeaconExplosionPassThroughShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cBeaconExplosionPassThroughShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cBeaconExplosionPassThroughShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
