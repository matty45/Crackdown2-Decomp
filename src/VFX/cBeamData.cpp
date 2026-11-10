// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "VFX/cGlobalLightShader.h"
#include "rws/classfactory.h"
#include "VFX/cBeamData.h"
#include "VFX/cBeamManager.h"
#include "cd2/memory.h"

namespace VFX
{
    RWS::CAttributeHandler *cBeamData::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cBeamData;
    }

    cBeamData::~cBeamData()
    {
    }

    const char *cBeamData::RetClassName() const
    {
        return "cBeamData";
    }

    // CD2 keeps the manager's registered-class getter in this object's range (table 0x82155350, slot 0).
    const Fun_Runtime::cClass &cBeamManager::RetClass() const
    {
        return *ms_pcBeamManagerClass;
    }

    static RWS::CClassFactory::CRegistrar cBeamDataRegistrar(
        "cBeamData", cBeamData::MakeNew, 0x88, false);

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
