#include "rws/attributes.h"
// Sim::cTimeOfDay (Crackdown 2): STAND-IN for the phase of the day only. RuffKing names. Evidence:
//   - m_fPhase (0x278; RuffKing 0x288): VFX::cAmbientVFXSpawner::CanSpawn (0x827F9840) reads ms_pInstance->m_fPhase,
//     and the
//     script method "RetPhase" (registered at 0x8239B390) is 0x823E7C40, which returns the float at 0x278.
//   - RetPhase's copy at 0x823E7C40 lies in cAiPlayer.cpp's range: the linker folded identical getters and kept the
//     copy from cAiPlayer's object, so src/AI/cAiPlayer.cpp defines it.
// g_cTimeOfDay is named after the type it is registered as ("cTimeOfDay", through 0x82772828; see AI/cAiPlayer.h).
// 0x82773C00 returns it: cTimeOfDay's RetScriptTypeRegistration, slot 1 of the cScriptHost table 0x82147930 that
// 0x82773FF4 installs. It stays open until this stand-in has its cScriptHost base. 0x82773C10..0x82773C30 return the
// AIE_TOD* registrars: slot 1 of those event classes' own tables.
// Known wrong, left for a structural fix: CD2 registers cTimeOfDay under Fun_Runtime::cScriptHost (inheritance registrar 0x830020B8) and
// GDb::cDebugPageHandler (0x83002120); the stand-in models neither base, so its fields sit at their CD2 offsets
// without the subobjects that hold them. RuffKing's bases differ (CAttributeHandler, CEventHandler, ... cDebugPageHandler).
#ifndef SIM_CTIMEOFDAY_H
#define SIM_CTIMEOFDAY_H

#include "cd2/layout.h"
#include "fun_runtime/class.h"

namespace Sim
{
    class cTimeOfDay
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTimeOfDayClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        unsigned char m_pad[0x278];
        float m_fPhase;                         // 0x278
        unsigned char m_unmodelled27C[0x284 - 0x27C];
        // RetPeriod's folded CD2 copy (0x825EC2E8); RuffKing names this field at phase +0xC too.
        float m_fPeriod;
        static cTimeOfDay *ms_pInstance;

        float RetPhase();
        float RetPeriod();

        CD2_LAYOUT_CHECKS(cTimeOfDay,
            CD2_OFFSET(cTimeOfDay, m_fPhase, 0x278)
            CD2_OFFSET(cTimeOfDay, m_fPeriod, 0x284))
    };
}

#endif // SIM_CTIMEOFDAY_H
