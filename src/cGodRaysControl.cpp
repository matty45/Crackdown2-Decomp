#include "VFX/cGodRaysRadialBlurShader.h"
#include "VFX/cGodRaysRaysRectShader.h"
#include "VFX/cGodRaysRestoreDepthShader.h"
#include "VFX/cGodRaysPassThroughShader.h"
#include "VFX/cGodRaysAddRaysShader.h"
#include "rws/classfactory.h"
#include "unknown/cGodRaysControl.h"

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
