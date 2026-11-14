// src/AudioLogic/cAudioBaseProfile.cpp
//
// Class: cAudioBaseProfile (namespace: AudioLogic). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cAudioBaseProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Audio/cAudioBaseProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AudioLogic/cAudioBaseProfile.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/scripthost.h"
#include "rws/classfactory.h"
#include "AudioLogic/cAudioBaseProfile.h"
#include "cd2/memory.h"
#include "fun_runtime/retval.h"

// CD2 calls the external wide-string assign instantiation at 0x82438418 with
// offset/count arguments; local LTCG specialization otherwise removes them.
extern template std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> > &
    std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> >::assign(
        const std::basic_string<wchar_t, std::char_traits<wchar_t>, Fun_Runtime::cAllocator<wchar_t> > &, size_t, size_t);

namespace AudioLogic
{
    const char *cAudioBaseProfile::RetClassName() const
    {
        return "cAudioBaseProfile";
    }

    Fun_Runtime::cClass &cAudioBaseProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAudioBaseProfileClass = new Fun_Runtime::cClass(0xAF0, "cAudioBaseProfile", 0x60);
        return *cAudioBaseProfileClass;
    }

    const Fun_Runtime::cClass *cAudioBaseProfile::ms_pcAudioBaseProfileClass = &cAudioBaseProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cAudioBaseProfile::RetClass() const
    {
        return *ms_pcAudioBaseProfileClass;
    }

    bool cAudioBaseProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAudioBaseProfileClass->IsA(c);
    }

    Fun_Runtime::RetVal cAudioBaseProfile::Init(const RWS::CAttributePacket &)
    {
        m_bReset = false;
        return Ret_OK;
    }

    Fun_Runtime::RetVal cAudioBaseProfile::Term()
    {
        m_bReset = false;
        return Ret_OK;
    }

    cAudioBaseProfile::~cAudioBaseProfile()
    {
        UnLinkMsg(m_Msg_Return_Audio_Self);
        UnRegisterMsg(m_Msg_Return_Audio_Self);
        m_bReset = false;
    }

    void cAudioBaseProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        RWS::CAttributeHandler::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cAudioBaseProfile"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    Fun_Runtime::cString profileName(it->GetAs_char_ptr());
                    m_sProfileName = profileName;
                }
                ReplaceLinkedMsg(m_Msg_Return_Audio_Self, it->GetAs_char_ptr(), "return cAudioBaseProfile*");
                break;
            }
        }
        m_bReset = false;
    }

    static RWS::CClassFactory::CRegistrar cAudioBaseProfileRegistrar(
        "cAudioBaseProfile", cAudioBaseProfile::MakeNew, 0x60, false);

    // CD2 0x82FA9ED8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAudioBaseProfilecScriptHostInheritRegistrar(
        AudioLogic::cAudioBaseProfile::StaticCreateClass(), Fun_Runtime::cScriptHost::StaticCreateClass());

    // CD2 0x82527770: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cAudioBaseProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAudioBaseProfile;
    }
}
