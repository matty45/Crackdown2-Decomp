// STAND-IN prefix only, through the volume RTPCs. CD2's global starts at 0x8392C200;
// constructor 0x8282E488 names the five RTPCs at +0x64..+0x94. Member names and the
// music/radio update pairing agree with RuffKing cAudioSystem; earlier storage is unmodelled.
#ifndef AUDIO_CAUDIOSYSTEM_H
#define AUDIO_CAUDIOSYSTEM_H

#include "Audio/cRTPC.h"

namespace Audio
{
    // RuffKing SetVoiceVolume names this flag; CD2's callback stores 0x83093337.
    extern bool g_bVOA;
    class cAudioSystem
    {
        unsigned char m_unmodelled0[0x64];
        cRTPC m_VolumeMusic;
        cRTPC m_VolumeRadio;
        cRTPC m_VolumeSFX;
        cRTPC m_VolumeVoice;
        cRTPC m_VolumeNPCVoice;
    public:
        // CD2 inlines both RTPC updates into UI::ApplyMusicVolume.
        __forceinline void SetMusicVolume(float value)
        {
            m_VolumeMusic.Set(value);
            m_VolumeRadio.Set(value);
        }
        inline void SetSFXVolume(float value) { m_VolumeSFX.Set(value); }
        inline void SetNPCVoiceVolume(float value) { m_VolumeNPCVoice.Set(value); }
        inline void SetVoiceVolume(float value)
        {
            m_VolumeVoice.Set(value);
            g_bVOA = value > 1.0f;
        }

        CD2_LAYOUT_CHECKS(cAudioSystem,
            CD2_OFFSET(cAudioSystem, m_VolumeMusic, 0x64)
            CD2_OFFSET(cAudioSystem, m_VolumeRadio, 0x70)
            CD2_OFFSET(cAudioSystem, m_VolumeSFX, 0x7C)
            CD2_OFFSET(cAudioSystem, m_VolumeVoice, 0x88)
            CD2_OFFSET(cAudioSystem, m_VolumeNPCVoice, 0x94))
    };
}

extern Audio::cAudioSystem g_AudioSystem;
#endif
