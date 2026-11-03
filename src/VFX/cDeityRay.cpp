#include "VFX/cDeityRaySampleMipsShader.h"
#include "VFX/cDeityRayAverageShader.h"
#include "VFX/cDeityRayFalloffShader.h"
#include "VFX/cDeityRayBlurOcclusionShader.h"
#include "VFX/cDeityRayShader.h"
#include "rws/classfactory.h"
#include "VFX/cDeityRay.h"
#include "VFX/cDeityRayOccludeShader.h"

namespace VFX
{
    cDeityRayOccludeShader *cDeityRayOccludeShader::ms_pInstance;

    bool cDeityRayOccludeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRayOccludeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRayOccludeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    const char *cDeityRay::RetClassName() const
    {
        return "cDeityRay";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cDeityRayRegistrar(
        "cDeityRay", cDeityRay::MakeNew, 0x6b0, false);
}

namespace VFX
{
    cDeityRayShader *cDeityRayShader::ms_pInstance;

    bool cDeityRayShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRayShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRayShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cDeityRayBlurOcclusionShader *cDeityRayBlurOcclusionShader::ms_pInstance;

    bool cDeityRayBlurOcclusionShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRayBlurOcclusionShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRayBlurOcclusionShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cDeityRayFalloffShader *cDeityRayFalloffShader::ms_pInstance;

    bool cDeityRayFalloffShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRayFalloffShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRayFalloffShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cDeityRayAverageShader *cDeityRayAverageShader::ms_pInstance;

    bool cDeityRayAverageShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRayAverageShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRayAverageShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cDeityRaySampleMipsShader *cDeityRaySampleMipsShader::ms_pInstance;

    bool cDeityRaySampleMipsShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDeityRaySampleMipsShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDeityRaySampleMipsShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
