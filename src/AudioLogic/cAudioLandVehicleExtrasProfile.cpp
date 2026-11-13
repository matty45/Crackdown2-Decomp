// src/AudioLogic/cAudioLandVehicleExtrasProfile.cpp
//
// Class: cAudioLandVehicleExtrasProfile (namespace: AudioLogic). Set up automatically: no function is matched yet. The
// address range and the evidence for it are in config/splits.txt; RuffKing's object for it is
// cAudioLandVehicleExtrasProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Audio/cAudioLandVehicleExtrasProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AudioLogic/cAudioLandVehicleExtrasProfile.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "AudioLogic/cAudioLandVehicleExtrasProfile.h"
#include "cd2/memory.h"

namespace AudioLogic
{
    RWS::CAttributeHandler *cAudioLandVehicleExtrasProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAudioLandVehicleExtrasProfile;
    }

    const char *cAudioLandVehicleExtrasProfile::RetClassName() const
    {
        return "cAudioLandVehicleExtrasProfile";
    }

    Fun_Runtime::cClass &cAudioLandVehicleExtrasProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAudioLandVehicleExtrasProfileClass = new Fun_Runtime::cClass(0xAF5, "cAudioLandVehicleExtrasProfile", 0x18C);
        return *cAudioLandVehicleExtrasProfileClass;
    }

    const Fun_Runtime::cClass *cAudioLandVehicleExtrasProfile::ms_pcAudioLandVehicleExtrasProfileClass = &cAudioLandVehicleExtrasProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cAudioLandVehicleExtrasProfile::RetClass() const
    {
        return *ms_pcAudioLandVehicleExtrasProfileClass;
    }

    bool cAudioLandVehicleExtrasProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAudioLandVehicleExtrasProfileClass->IsA(c);
    }

    Fun_Runtime::RetVal cAudioLandVehicleExtrasProfile::Init(const RWS::CAttributePacket &)
    {
        m_bReset = false;
        return Ret_OK;
    }

    Fun_Runtime::RetVal cAudioLandVehicleExtrasProfile::Term()
    {
        m_bReset = false;
        return Ret_OK;
    }

    void cAudioLandVehicleExtrasProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cAudioBaseProfile::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cAudioLandVehicleExtrasProfile"); !it.IsFinished(); ++it)
        {
            // ParseRWS retains the mutable text parameter declared by the reference API.
            switch (it->GetCommandId())
            {
            case CMD_TAKEOFF_RPM_VS_TIME:
                AudioEngine::cAudioGraph::ParseRWS(const_cast<char *>(it->GetAs_char_ptr()), m_TakeoffRPMVsTime);
                break;
            case CMD_DISENGAGE_RPM_VS_TIME:
                AudioEngine::cAudioGraph::ParseRWS(const_cast<char *>(it->GetAs_char_ptr()), m_GearDisengageRPMVsTime);
                break;
            case CMD_ENGAGE_RPM_VS_TIME:
                AudioEngine::cAudioGraph::ParseRWS(const_cast<char *>(it->GetAs_char_ptr()), m_GearEngageRPMVsTime);
                break;
            case CMD_DISENGAGE_LOAD_VS_TIME:
                AudioEngine::cAudioGraph::ParseRWS(const_cast<char *>(it->GetAs_char_ptr()), m_GearDisengageLoadVsTime);
                break;
            case CMD_ENGAGE_LOAD_VS_TIME:
                AudioEngine::cAudioGraph::ParseRWS(const_cast<char *>(it->GetAs_char_ptr()), m_GearEngageLoadVsTime);
                break;
            }
        }
    }

    static RWS::CClassFactory::CRegistrar cAudioLandVehicleExtrasProfileRegistrar(
        "cAudioLandVehicleExtrasProfile", cAudioLandVehicleExtrasProfile::MakeNew, 0x18C, false);

    // CD2 0x82FA9FF0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAudioLandVehicleExtrasProfilecNonGameBaseInheritRegistrar(
        AudioLogic::cAudioLandVehicleExtrasProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}
