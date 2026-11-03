#include "VFX/cNoiseVolumesRestoreDepthShader.h"
#include "VFX/cNoiseVolumesEdgeDetectShader.h"
#include "VFX/cNoiseVolumesFogComposeEdgeShader.h"
#include "VFX/cNoiseVolumesFogComposeShader.h"
#include "VFX/cNoiseVolumesPassThroughShader.h"
#include "VFX/cNoiseVolumes5OctavesShader.h"
#include "VFX/cNoiseVolumes4OctavesShader.h"
#include "VFX/cNoiseVolumes3OctavesShader.h"
#include "VFX/cNoiseVolumes2OctavesShader.h"
#include "VFX/cNoiseVolumes1OctavesShader.h"
#include "rws/classfactory.h"
#include "unknown/cNoiseVolumesControl.h"

namespace unknown
{
    const char *cNoiseVolumesControl::RetClassName() const
    {
        return "cNoiseVolumesControl";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cNoiseVolumesControlRegistrar(
        "cNoiseVolumesControl", cNoiseVolumesControl::MakeNew, 0x1c, false);
}

namespace VFX
{
    cNoiseVolumes1OctavesShader *cNoiseVolumes1OctavesShader::ms_pInstance;

    bool cNoiseVolumes1OctavesShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumes1OctavesShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumes1OctavesShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumes2OctavesShader *cNoiseVolumes2OctavesShader::ms_pInstance;

    bool cNoiseVolumes2OctavesShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumes2OctavesShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumes2OctavesShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumes3OctavesShader *cNoiseVolumes3OctavesShader::ms_pInstance;

    bool cNoiseVolumes3OctavesShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumes3OctavesShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumes3OctavesShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumes4OctavesShader *cNoiseVolumes4OctavesShader::ms_pInstance;

    bool cNoiseVolumes4OctavesShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumes4OctavesShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumes4OctavesShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumes5OctavesShader *cNoiseVolumes5OctavesShader::ms_pInstance;

    bool cNoiseVolumes5OctavesShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumes5OctavesShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumes5OctavesShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumesPassThroughShader *cNoiseVolumesPassThroughShader::ms_pInstance;

    bool cNoiseVolumesPassThroughShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumesPassThroughShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumesPassThroughShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumesFogComposeShader *cNoiseVolumesFogComposeShader::ms_pInstance;

    bool cNoiseVolumesFogComposeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumesFogComposeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumesFogComposeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumesFogComposeEdgeShader *cNoiseVolumesFogComposeEdgeShader::ms_pInstance;

    bool cNoiseVolumesFogComposeEdgeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumesFogComposeEdgeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumesFogComposeEdgeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumesEdgeDetectShader *cNoiseVolumesEdgeDetectShader::ms_pInstance;

    bool cNoiseVolumesEdgeDetectShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumesEdgeDetectShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumesEdgeDetectShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cNoiseVolumesRestoreDepthShader *cNoiseVolumesRestoreDepthShader::ms_pInstance;

    bool cNoiseVolumesRestoreDepthShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cNoiseVolumesRestoreDepthShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cNoiseVolumesRestoreDepthShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}
