// AudioEngine::cAudioGraph: RuffKing names and layout. CD2 extras-profile
// factory 0x82527CF8 constructs five 0x3C graphs, clearing each count at +0x38.
#ifndef AUDIOENGINE_CAUDIOGRAPH_H
#define AUDIOENGINE_CAUDIOGRAPH_H

#include "cd2/layout.h"

namespace AudioEngine
{
    class cAudioGraph
    {
    public:
        cAudioGraph() : m_nNumPoints(0) {}
        static bool ParseRWS(char *, cAudioGraph &);

    protected:
        float m_aInputs[7];
        float m_aOutputs[7];
        int m_nNumPoints;

        CD2_LAYOUT_CHECKS(cAudioGraph,
            CD2_SIZE(cAudioGraph, 0x3C)
            CD2_OFFSET(cAudioGraph, m_aInputs, 0)
            CD2_OFFSET(cAudioGraph, m_aOutputs, 0x1C)
            CD2_OFFSET(cAudioGraph, m_nNumPoints, 0x38))
    };
}

#endif
