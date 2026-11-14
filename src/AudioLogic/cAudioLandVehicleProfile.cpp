// src/AudioLogic/cAudioLandVehicleProfile.cpp
//
// Class: cAudioLandVehicleProfile (namespace: AudioLogic). Set up automatically: no function is matched yet. The
// address range and the evidence for it are in config/splits.txt; RuffKing's object for it is
// cAudioLandVehicleProfile.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Audio/cAudioLandVehicleProfile.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/AudioLogic/cAudioLandVehicleProfile.cpp

#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "AudioLogic/cAudioLandVehicleProfile.h"
#include "cd2/memory.h"
#include "AudioLogic/cAudioLandVehicleExtrasProfile.h"
#include "rw/rwmem.h"
#include <string.h>

namespace AudioLogic
{
    RWS::CAttributeHandler *cAudioLandVehicleProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cAudioLandVehicleProfile;
    }

    const char *cAudioLandVehicleProfile::RetClassName() const
    {
        return "cAudioLandVehicleProfile";
    }

    Fun_Runtime::cClass &cAudioLandVehicleProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAudioLandVehicleProfileClass = new Fun_Runtime::cClass(0xAF1, "cAudioLandVehicleProfile", 0x7C);
        return *cAudioLandVehicleProfileClass;
    }

    const Fun_Runtime::cClass *cAudioLandVehicleProfile::ms_pcAudioLandVehicleProfileClass = &cAudioLandVehicleProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cAudioLandVehicleProfile::RetClass() const
    {
        return *ms_pcAudioLandVehicleProfileClass;
    }

    bool cAudioLandVehicleProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAudioLandVehicleProfileClass->IsA(c);
    }

    Fun_Runtime::RetVal cAudioLandVehicleProfile::Init(const RWS::CAttributePacket &)
    {
        m_bReset = false;
        return Ret_OK;
    }

    Fun_Runtime::RetVal cAudioLandVehicleProfile::Term()
    {
        m_bReset = false;
        return Ret_OK;
    }

    void cAudioLandVehicleProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cAudioBaseProfile::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cAudioLandVehicleProfile"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_FAKEREV_PEAK_LIMIT:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fFakeRevPeakRPM = value;
                }
                break;
            case CMD_FAKEREV_RAMPUP_TIME:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fFakeRevRampUp = value;
                }
                break;
            case CMD_FAKEREV_RAMPDOWN_TIME:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fFakeRevRampDown = value;
                }
                break;
            case CMD_FAKEREV_DELAY_TIME:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fFakeRevStartDelay = value;
                }
                break;
            case CMD_AUDIO_RPM_MIN:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fAudioRPMMin = value;
                }
                break;
            case CMD_AUDIO_RPM_MAX:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, sizeof(value));
                    m_fAudioRPMMax = value;
                }
                break;
            case CMD_MSG_GET_EXTRAS_PROFILE:
                if (strlen(it->GetAs_char_ptr()))
                    m_pExtrasProfile = static_cast<cAudioLandVehicleExtrasProfile *>(GetAudioProfile(it->GetAs_char_ptr()));
                else
                    m_pExtrasProfile = 0;
                break;
            }
        }
    }

    static RWS::CClassFactory::CRegistrar cAudioLandVehicleProfileRegistrar(
        "cAudioLandVehicleProfile", cAudioLandVehicleProfile::MakeNew, 0x7C, false);

    // CD2 0x82FAA0D0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAudioLandVehicleProfilecNonGameBaseInheritRegistrar(
        AudioLogic::cAudioLandVehicleProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}
