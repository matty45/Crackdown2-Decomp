// AI::cJunctionNodeController (Crackdown 2): STAND-IN for its signal-colour enum only; the class itself is not
// modelled. Values from Prop::cTrafficLight::FindFrame (0x82747AF0), which builds "_PROPLIGHT_TLGREEN_%d" for 0,
// "_PROPLIGHT_TLAMBER_%d" for 1 and "_PROPLIGHT_TLRED_%d" for 2; the enumerator names are ours.
#ifndef AI_CJUNCTIONNODECONTROLLER_H
#define AI_CJUNCTIONNODECONTROLLER_H

namespace AI
{
    class cJunctionNodeController
    {
    public:
        enum eSignalColour
        {
            eSignalColour_Green = 0,
            eSignalColour_Amber = 1,
            eSignalColour_Red = 2
        };
    };
}

#endif // AI_CJUNCTIONNODECONTROLLER_H
