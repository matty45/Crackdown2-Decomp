// Recovered declaration: RuffKing GameAudio.cpp; CD2 UI option callbacks call 0x8282EBF8.
#ifndef AUDIO_GAMEAUDIO_H
#define AUDIO_GAMEAUDIO_H

#include "Audio/cAudioSystem.h"

namespace Audio
{
    void SetDynamicRange(unsigned int nSetting, bool bOn);
    // CD2 inlines the global-system forwarding wrapper and both cached RTPC updates.
    __forceinline void SetMusicVolume(float value) { g_AudioSystem.SetMusicVolume(value); }
    inline void SetSFXVolume(float value) { g_AudioSystem.SetSFXVolume(value); }
    inline void SetNPCVoiceVolume(float value) { g_AudioSystem.SetNPCVoiceVolume(value); }
    inline void SetVoiceVolume(float value) { g_AudioSystem.SetVoiceVolume(value); }
}

#endif
