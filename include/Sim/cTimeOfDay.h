// Sim::cTimeOfDay (Crackdown 2): STAND-IN for the phase of the day only. RuffKing names. Evidence:
//   - m_fPhase (0x278; RuffKing 0x288): VFX::cAmbientVFXSpawner::CanSpawn (0x827F9840) reads ms_pInstance->m_fPhase,
//     and the
//     script method "RetPhase" (registered at 0x8239B390) is 0x823E7C40, which returns the float at 0x278.
//   - RetPhase's copy at 0x823E7C40 lies in cAiPlayer.cpp's range: the linker folded identical getters and kept the
//     copy from cAiPlayer's object, so src/AI/cAiPlayer.cpp defines it.
#ifndef SIM_CTIMEOFDAY_H
#define SIM_CTIMEOFDAY_H

#include "cd2/layout.h"

namespace Sim
{
    class cTimeOfDay
    {
    public:
        unsigned char m_pad[0x278];
        float m_fPhase;                         // 0x278
        static cTimeOfDay *ms_pInstance;

        float RetPhase();

        CD2_LAYOUT_CHECKS(cTimeOfDay,
            CD2_OFFSET(cTimeOfDay, m_fPhase, 0x278))
    };
}

#endif // SIM_CTIMEOFDAY_H
