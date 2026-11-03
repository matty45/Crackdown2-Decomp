#include "VFX/cGlobalLightShader.h"
#include "rws/classfactory.h"
#include "VFX/cBeamData.h"

namespace VFX
{
    const char *cBeamData::RetClassName() const
    {
        return "cBeamData";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cBeamDataRegistrar(
        "cBeamData", cBeamData::MakeNew, 0x88, false);
}

namespace VFX
{
    cGlobalLightShader *cGlobalLightShader::ms_pInstance;

    bool cGlobalLightShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cGlobalLightShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cGlobalLightShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
