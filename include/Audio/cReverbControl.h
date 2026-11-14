// Audio::cReverbControl (Crackdown 2): STAND-IN for the static exit entry point only. RuffKing's cReverbControl.h
// declares it; CD2's reverb zone (0x8280F858) calls it at 0x823B7C70 with the zone's layer type. The class's layout and
// its other entry points are not modelled.
#ifndef AUDIO_CREVERBCONTROL_H
#define AUDIO_CREVERBCONTROL_H

namespace Audio
{
    class cReverbControl
    {
    public:
        static void Exit(unsigned int layertype);
    };
}

#endif // AUDIO_CREVERBCONTROL_H
