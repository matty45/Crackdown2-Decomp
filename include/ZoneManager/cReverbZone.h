// ZoneManager::cReverbZone: STAND-IN. Base and m_strName from RuffKing; CD2's destructor (0x8280EF80) frees a wide string at
// 0xE0 (8-wchar buffer) before cPlayerTriggerBase's destructor. Size 0x150 (registrar).
#ifndef ZoneManager_cReverbZone_H
#define ZoneManager_cReverbZone_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "fun_runtime/string.h"
#include "cd2/layout.h"

namespace ZoneManager
{
    class cReverbZone : public cPlayerTriggerZone
    {
    public:
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // __forceinline: CD2 inlines it into MakeNew (0x8280EE88).
        __forceinline cReverbZone(const RWS::CAttributePacket &)
            : cPlayerTriggerZone(true), m_bPreviouslyEntered(false), m_bPreviouslyLeft(false) {}
        virtual ~cReverbZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        Fun_Runtime::cString m_strName;             // 0xE0
        // RuffKing's settings, then its flags without the debug colour before them (MakeNew clears 0x140/0x141).
        unsigned int m_nType;                       // 0xFC
        unsigned int m_nLayerType;
        unsigned int m_nWetLevel;
        unsigned int m_nDryLevel;
        unsigned int m_nHFRatio;
        unsigned int m_nReverbTime;
        unsigned int m_nReverbDiffusion;
        unsigned int m_nReverbERLevel;
        unsigned int m_nReverbEQ1Gain;
        unsigned int m_nReverbEQ1Freq;
        unsigned int m_nReverbEQ1Q;
        unsigned int m_nReverbEQ2Gain;
        unsigned int m_nReverbEQ2Freq;
        unsigned int m_nReverbEQ2Q;
        unsigned int m_nReverbEQ3Gain;
        unsigned int m_nReverbEQ3Freq;
        unsigned int m_nReverbEQ3Q;                 // 0x13C
        bool m_bPreviouslyEntered;                  // 0x140
        bool m_bPreviouslyLeft;                     // 0x141

        CD2_LAYOUT_CHECKS(cReverbZone,
            CD2_SIZE(cReverbZone, 0x150)
            CD2_OFFSET(cReverbZone, m_strName, 0xE0)
            CD2_OFFSET(cReverbZone, m_nType, 0xFC)
            CD2_OFFSET(cReverbZone, m_bPreviouslyEntered, 0x140))
    };
}

#endif
