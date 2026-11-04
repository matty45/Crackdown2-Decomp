#include "VFX/cSkidMarksShader.h"
#include "rws/classfactory.h"
// src/VFX/cSkidMarks.cpp
//
// Class: cSkidMarks (namespace: VFX). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cSkidMarks.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/cSkidMarks.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cSkidMarks.cpp

#include "VFX/cSkidMarks.h"

namespace VFX
{
    const char *cSkidMarks::RetClassName() const
    {
        return "cSkidMarks";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cSkidMarksRegistrar(
        "cSkidMarks", cSkidMarks::MakeNew, 0x2cc, false);
}

namespace VFX
{
    cSkidMarksShader *cSkidMarksShader::ms_pInstance;

    bool cSkidMarksShader::ReloadInstance(bool revert)
    {
        if (ms_pInstance)
        {
            ms_pInstance->Reload(revert);
            cSkidMarksShader *shader = ms_pInstance;
            Ext_82B8A7B0(shader->m_pVertexShader);
            Ext_82B8A780(shader->m_pPixelShader);
        }
        return true;
    }

    cShader::ReloadCallback cSkidMarksShader::GetReloadCallback() const
    {
        return ReloadInstance;
    }
}

#include "cd2/memory.h"

// CD2 0x827B7A90: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cSkidMarks::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSkidMarks;
    }
}
