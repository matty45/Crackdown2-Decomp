#include "VFX/cSimplePostProcessShader.h"
#include "VFX/cPostProcessShader.h"
#include "rws/classfactory.h"
#include "VFX/cPostProcessControl.h"

namespace VFX
{
    const char *cPostProcessControl::RetClassName() const
    {
        return "cPostProcessControl";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cPostProcessControlRegistrar(
        "cPostProcessControl", cPostProcessControl::MakeNew, 0x1c, false);
}

namespace VFX
{
    cPostProcessShader *cPostProcessShader::ms_pInstance;

    bool cPostProcessShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cPostProcessShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cPostProcessShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cSimplePostProcessShader *cSimplePostProcessShader::ms_pInstance;

    bool cSimplePostProcessShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cSimplePostProcessShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cSimplePostProcessShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
