#include "VFX/cGodRaysRadialBlurShader.h"
#include "VFX/cGodRaysRaysRectShader.h"
#include "VFX/cGodRaysRestoreDepthShader.h"
#include "VFX/cGodRaysPassThroughShader.h"
#include "VFX/cGodRaysAddRaysShader.h"
#include "rws/classfactory.h"
#include "unknown/cGodRaysControl.h"
#include "VFX/godrays.h"
#include <stdlib.h>

namespace unknown
{
    const char *cGodRaysControl::RetClassName() const
    {
        return "cGodRaysControl";
    }

    static RWS::CClassFactory::CRegistrar cGodRaysControlRegistrar(
        "cGodRaysControl", cGodRaysControl::MakeNew, 0x1c, false);
}

namespace VFX
{
    float g_fGodRaysCloudBlockFactor = 2.0f;
    float g_fGodRaysFalloffFactor = 1.2f;
    float g_fGodRaysMagnificationFactor = 0.71f;
    float g_fGodRaysSize = 350.0f;
    int g_nGodRaysMode;
    int g_nGodRaysTry;

    void SetGodRaysCloudBlockFactor(void *, wchar_t *argument)
    {
        g_fGodRaysCloudBlockFactor = static_cast<float>(_wtof(argument));
    }

    void SetGodRaysFalloffFactor(void *, wchar_t *argument)
    {
        g_fGodRaysFalloffFactor = static_cast<float>(_wtof(argument));
    }

    void SetGodRaysMagnificationFactor(void *, wchar_t *argument)
    {
        g_fGodRaysMagnificationFactor = static_cast<float>(_wtof(argument));
    }

    void SetGodRaysSize(void *, wchar_t *argument)
    {
        g_fGodRaysSize = static_cast<float>(_wtof(argument));
    }

    void SetGodRaysMode(void *, wchar_t *argument)
    {
        g_nGodRaysMode = _wtoi(argument);
    }

    void SetGodRaysTry(void *, wchar_t *argument)
    {
        g_nGodRaysTry = _wtoi(argument);
    }

    cGodRaysAddRaysShader *cGodRaysAddRaysShader::ms_pInstance;

    bool cGodRaysAddRaysShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGodRaysAddRaysShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGodRaysAddRaysShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    cGodRaysPassThroughShader *cGodRaysPassThroughShader::ms_pInstance;

    bool cGodRaysPassThroughShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGodRaysPassThroughShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGodRaysPassThroughShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    cGodRaysRestoreDepthShader *cGodRaysRestoreDepthShader::ms_pInstance;

    bool cGodRaysRestoreDepthShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGodRaysRestoreDepthShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGodRaysRestoreDepthShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    cGodRaysRaysRectShader *cGodRaysRaysRectShader::ms_pInstance;

    bool cGodRaysRaysRectShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGodRaysRaysRectShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGodRaysRaysRectShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }

    cGodRaysRadialBlurShader *cGodRaysRadialBlurShader::ms_pInstance;

    bool cGodRaysRadialBlurShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGodRaysRadialBlurShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGodRaysRadialBlurShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
