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
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cScatterMeshResourcesRegistrar(
        "cScatterMeshResources", cScatterMeshResources::MakeNew, 0x1c, false);
}

namespace VFX
{
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
}

namespace VFX
{
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
