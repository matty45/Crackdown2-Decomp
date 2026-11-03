#include "VFX/cDOFShader.h"
#include "VFX/cDOFCalcBlurShader.h"
#include "rws/classfactory.h"
#include "VFX/cDepthOfField.h"

namespace VFX
{
    const char *cDepthOfField::RetClassName() const
    {
        return "cDepthOfField";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cDepthOfFieldRegistrar(
        "cDepthOfField", cDepthOfField::MakeNew, 0x8c, false);
}

namespace VFX
{
    cDOFCalcBlurShader *cDOFCalcBlurShader::ms_pInstance;

    bool cDOFCalcBlurShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDOFCalcBlurShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDOFCalcBlurShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cDOFShader *cDOFShader::ms_pInstance;

    bool cDOFShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cDOFShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cDOFShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
