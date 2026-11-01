// STAND-IN for CD2's older RTPC representation. Constructor 0x8282E488 initializes
// ID/name/value triples; UI callbacks compare/store +8 and pass +0 to SetRTPCValue.
// RuffKing names the wrapper cRTPC and its cached float m_fValue; ID/name member names are ours.
#ifndef AUDIO_CRTPC_H
#define AUDIO_CRTPC_H

#include "cd2/layout.h"

namespace AK
{
    namespace SoundEngine
    {
        // CD2 0x82CD5AF8; the global game-object ID is unsigned -1.
        int SetRTPCValue(unsigned int id, float value, unsigned int gameObjectID);
    }
}

namespace Audio
{
    class cRTPC
    {
        unsigned int m_nRTPCID;
        const char *m_pszRTPCName;
        float m_fValue;
    public:
        inline void Set(float value)
        {
            if (value != m_fValue)
            {
                m_fValue = value;
                AK::SoundEngine::SetRTPCValue(m_nRTPCID, value, ~0u);
            }
        }

        CD2_LAYOUT_CHECKS(cRTPC,
            CD2_SIZE(cRTPC, 12)
            CD2_OFFSET(cRTPC, m_nRTPCID, 0)
            CD2_OFFSET(cRTPC, m_pszRTPCName, 4)
            CD2_OFFSET(cRTPC, m_fValue, 8))
    };
}
#endif
