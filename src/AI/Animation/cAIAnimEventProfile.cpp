#include "rws/classfactory.h"
#include "fun_runtime/retval.h"
// src/AI/Animation/cAIAnimEventProfile.cpp
//
// Class: cAIAnimEventProfile (namespace: AI). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cAIAnimEventProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/AI/Animation/cAIAnimEventProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AI/Animation/cAIAnimEventProfile.cpp

#include "AI/cAIAnimEventProfile.h"
#include "rw/rwmem.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"

namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAIAnimEventProfilecNonGameBaseInheritRegistrar(
        cAIAnimEventProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    void cAIAnimEventProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        RWS::CAttributeHandler::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cAIAnimEventProfile"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    float radius = it->GetAs_float();
                    RwMemNative32(&radius, sizeof(radius));
                    m_fRadius = radius;
                }
                break;
            case 1:
                m_nAIAnimEventType = (etAIAnimEventType)rwSwap32(it->GetAs_UInt32());
                break;
            case 2:
                {
                    Fun_Runtime::cString profileName(it->GetAs_char_ptr());
                    m_sProfileName = profileName;
                }
                ReplaceLinkedMsg(m_Msg_Return_Self, it->GetAs_char_ptr(), "return cAIAnimEventProfile*");
                break;
            }
        }
    }

    RWS::CAttributeHandler *cAIAnimEventProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAIAnimEventProfile;
    }

    const char *cAIAnimEventProfile::RetClassName() const
    {
        return "cAIAnimEventProfile";
    }
}

#include "cd2/memory.h"

namespace AI
{
    Fun_Runtime::cClass &cAIAnimEventProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAIAnimEventProfileClass = new Fun_Runtime::cClass(0x9FCE4, "cAIAnimEventProfile", 0x4C);
        return *cAIAnimEventProfileClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cAIAnimEventProfile::ms_pcAIAnimEventProfileClass = &cAIAnimEventProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cAIAnimEventProfile::RetClass() const
    {
        return *ms_pcAIAnimEventProfileClass;
    }
}

namespace AI
{
    bool cAIAnimEventProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAIAnimEventProfileClass->IsA(c);
    }
}

namespace AI
{
    Fun_Runtime::RetVal cAIAnimEventProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    Fun_Runtime::RetVal cAIAnimEventProfile::Term()
    {
        return Ret_OK;
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAIAnimEventProfileRegistrar(
        "cAIAnimEventProfile", cAIAnimEventProfile::MakeNew, 0x4C, false);
}
