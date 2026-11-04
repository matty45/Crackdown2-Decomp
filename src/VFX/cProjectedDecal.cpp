#include "VFX/cClippedPlanarDecalShader.h"
#include "VFX/cLargePlanarDecalMultiplicativeShader.h"
#include "VFX/cLargePlanarDecalShader.h"
#include "VFX/cHemisphericalDecalMultiplicativeShader.h"
#include "VFX/cHemisphericalDecalShader.h"
#include "VFX/cPlanarDecalMultiplicativeShader.h"
#include "VFX/cPlanarDecalShader.h"
#include "VFX/cSphericalDecalMultiplicativeShader.h"
#include "VFX/cSphericalDecalShader.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/VFX/cProjectedDecal.cpp
//
// Class: cProjectedDecal (namespace: VFX). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cProjectedDecal.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cProjectedDecal.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cProjectedDecal.cpp

#include "VFX/cProjectedDecal.h"

namespace VFX
{
    const char *cProjectedDecal::RetClassName() const
    {
        return "cProjectedDecal";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cProjectedDecal::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cProjectedDecalClass = new Fun_Runtime::cClass(0x1EE7F00D, "cProjectedDecal", 0x28C);
        return *cProjectedDecalClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cProjectedDecal::ms_pcProjectedDecalClass = &cProjectedDecal::StaticCreateClass();
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cProjectedDecalRegistrar(
        "cProjectedDecal", cProjectedDecal::MakeNew, 0x28C, false);
}

// CD2 0x83007BF8: runtime class inheritance registration.
namespace VFX
{
    static Fun_Runtime::cInheritanceRegistrar cProjectedDecalcNonGameBaseInheritRegistrar(
        VFX::cProjectedDecal::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

namespace VFX
{
    cSphericalDecalShader *cSphericalDecalShader::ms_pInstance;

    bool cSphericalDecalShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cSphericalDecalShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cSphericalDecalShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cSphericalDecalMultiplicativeShader *cSphericalDecalMultiplicativeShader::ms_pInstance;

    bool cSphericalDecalMultiplicativeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cSphericalDecalMultiplicativeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cSphericalDecalMultiplicativeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cPlanarDecalShader *cPlanarDecalShader::ms_pInstance;

    bool cPlanarDecalShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cPlanarDecalShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cPlanarDecalShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cPlanarDecalMultiplicativeShader *cPlanarDecalMultiplicativeShader::ms_pInstance;

    bool cPlanarDecalMultiplicativeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cPlanarDecalMultiplicativeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cPlanarDecalMultiplicativeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cHemisphericalDecalShader *cHemisphericalDecalShader::ms_pInstance;

    bool cHemisphericalDecalShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cHemisphericalDecalShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cHemisphericalDecalShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cHemisphericalDecalMultiplicativeShader *cHemisphericalDecalMultiplicativeShader::ms_pInstance;

    bool cHemisphericalDecalMultiplicativeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cHemisphericalDecalMultiplicativeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cHemisphericalDecalMultiplicativeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cLargePlanarDecalShader *cLargePlanarDecalShader::ms_pInstance;

    bool cLargePlanarDecalShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cLargePlanarDecalShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cLargePlanarDecalShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cLargePlanarDecalMultiplicativeShader *cLargePlanarDecalMultiplicativeShader::ms_pInstance;

    bool cLargePlanarDecalMultiplicativeShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cLargePlanarDecalMultiplicativeShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cLargePlanarDecalMultiplicativeShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

namespace VFX
{
    cClippedPlanarDecalShader *cClippedPlanarDecalShader::ms_pInstance;

    bool cClippedPlanarDecalShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cClippedPlanarDecalShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cClippedPlanarDecalShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

// CD2 0x827A5640: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cProjectedDecal::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cProjectedDecal;
    }
}
