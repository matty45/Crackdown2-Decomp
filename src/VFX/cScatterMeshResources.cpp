// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "VFX/cScatterUnpackShader.h"
#include "VFX/cScatterUnpackIndexedShader.h"
#include "rws/classfactory.h"
#include "VFX/cScatterMeshResources.h"
#include "cd2/memory.h"

namespace VFX
{
    RWS::CAttributeHandler *cScatterMeshResources::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cScatterMeshResources;
    }

    const char *cScatterMeshResources::RetClassName() const
    {
        return "cScatterMeshResources";
    }

    static RWS::CClassFactory::CRegistrar cScatterMeshResourcesRegistrar(
        "cScatterMeshResources", cScatterMeshResources::MakeNew, 0x1c, false);

    cScatterUnpackIndexedShader *cScatterUnpackIndexedShader::ms_pInstance;

    bool cScatterUnpackIndexedShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cScatterUnpackIndexedShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cScatterUnpackIndexedShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    cScatterUnpackShader *cScatterUnpackShader::ms_pInstance;

    bool cScatterUnpackShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cScatterUnpackShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cScatterUnpackShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
