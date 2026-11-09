// Sim::cTimeOfDay (Crackdown 2): STAND-IN with CD2's base chain and selected own fields. RuffKing names. Evidence:
//   - m_fPhase (0x278; RuffKing 0x288): VFX::cAmbientVFXSpawner::CanSpawn (0x827F9840) reads ms_pInstance->m_fPhase,
//     and the
//     script method "RetPhase" (registered at 0x8239B390) is 0x823E7C40, which returns the float at 0x278.
//   - RetPhase's copy at 0x823E7C40 lies in cAiPlayer.cpp's range: the linker folded identical getters and kept the
//     copy from cAiPlayer's object, so src/AI/cAiPlayer.cpp defines it.
// g_cTimeOfDay is named after the type it is registered as ("cTimeOfDay", through 0x82772828; see AI/cAiPlayer.h).
// 0x82773C00 returns it: cTimeOfDay's RetScriptTypeRegistration, slot 1 of the cScriptHost table 0x82147930 that
// 0x82773FF4 installs. 0x82773C10..0x82773C30 return the
// AIE_TOD* registrars: slot 1 of those event classes' own tables.
// Constructor 0x82773F00 establishes CAttributeHandler +0, CEventHandler +0x18, cScriptHost +0x1C,
// cDebugPageHandler +0x38, cLoadSaveObject +0x3C, cReplicatedClass +0x40 and cNetRoleObject +0x270.
// The last base ends at +0x278, exactly where the phase starts. Its primary table 0x821478E4 has 13 slots:
// the 11 CAttributeHandler slots, RetClassName at 11 and Destruct at 12. Descriptor/factory size is 0x2B0.
#ifndef SIM_CTIMEOFDAY_H
#define SIM_CTIMEOFDAY_H

#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "fun_runtime/scripthost.h"
#include "GDb/cDebugPageHandler.h"
#include "SaveGame/cLoadSaveObject.h"
#include "network/cReplicatedClass.h"
#include "network/netrole.h"
#include "fun_runtime/script_type_registrar.h"

namespace Sim
{
    class cTimeOfDay : public RWS::CAttributeHandler, public RWS::CEventHandler,
        public Fun_Runtime::cScriptHost, public GDb::cDebugPageHandler, public SaveGame::cLoadSaveObject,
        public cReplicatedClass, public Network::cNetRoleObject
    {
    public:
        cTimeOfDay(); // CD2 0x82773F00, called by MakeNew
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTimeOfDayClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual void HandleEvents(RWS::CMsg &);
        // CD2's replicated-class table 0x82147968 supplies these formerly pure interface slots.
        virtual bool IsSequential() const;
        virtual bool IsOwnedLocally();
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        float m_fPhase;                         // 0x278
        unsigned char m_unmodelled27C[0x284 - 0x27C];
        // RetPeriod's folded CD2 copy (0x825EC2E8); RuffKing names this field at phase +0xC too.
        float m_fPeriod;
    private:
        // RuffKing names; CD2 console callback 0x82774798 toggles the force flag at +0x289.
        bool m_bActive;
        bool m_bForceUpdatePhaseStep;
        unsigned char m_unmodelled28A[0x2B0 - 0x28A];
    public:
        static cTimeOfDay *ms_pInstance;

        float RetPhase();
        float RetPeriod();
        void SetForceUpdatePhaseStep(bool force) { m_bForceUpdatePhaseStep = force; }
        bool RetForceUpdatePhaseStep() { return m_bForceUpdatePhaseStep; }

        CD2_LAYOUT_CHECKS(cTimeOfDay,
            CD2_SIZE(cTimeOfDay, 0x2B0)
            CD2_OFFSET(cTimeOfDay, m_fPhase, 0x278)
            CD2_OFFSET(cTimeOfDay, m_fPeriod, 0x284)
            CD2_OFFSET(cTimeOfDay, m_bForceUpdatePhaseStep, 0x289))
    };

    // Console callback name and signature from RuffKing; CD2 registers it at 0x82774944.
    void TODForceUpdatePhase(void *, wchar_t *);
}

extern Fun_Runtime::cScriptTypeRegistrar<Sim::cTimeOfDay> g_cTimeOfDay;

#endif // SIM_CTIMEOFDAY_H
