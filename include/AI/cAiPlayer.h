// AI::cAiPlayer (Crackdown 2): the interface of an AI-controlled character. STAND-IN, sized to CD2; RuffKing names.
// Evidence:
//   - Size 0x620: the code at 0x823E7C88 builds cClass(5, "cAiPlayer", 0x620). Base cCharacterEntityIF: the
//     constructor 0x823E8650 first calls cCharacterEntityIF's (0x823EF240), and the initializer 0x82F605D0 registers
//     "cAIPlayer" as inheriting "cCharacterEntityIF", as in RuffKing. RuffKing's second base (cAIEventHandler) has no
//     vptr store in CD2's constructor: not modelled.
//   - m_DamageCache (0x540): the first field after the base, built by the constructor (AI/AIDamageCache.h).
//   - The script methods registered by 0x823E7CE0 (the virtual of cAiPlayer's method registrar, installed by
//     0x82F605D0) name these fields: "SetMapStatus" (0x823E79B8 stores 0x60C; RuffKing: SetMapStatus, etMapStatus
//     m_nMapStatus), "SetFriendlyFireTolerance" (0x823E79C0: 0x5F8), "SetCombatFriendlyFireTolerance" (0x823E79C8:
//     0x5FC), "SetShotsRemaining" (0x823E79F0: halfword 0x614), "Set/IsInterestingObjectReactionEnabled" (0x823E79D8 /
//     0x823E79D0: 0x616), "Set/RetInterestingObjectPriority" (0x823E79E8 / 0x823E79E0: 0x617), "RetOwnedVehicle"
//     (0x823E79F8: the safe pointer at 0x5D8, whose object pointer is at 0x5E4) and "RecallDamageCaused" (0x823E8DC8).
//   - The constructor stores safe-pointer vptrs at 0x5D8 and 0x5E8; matched code uses only the first.
//   - Virtuals: RetName is slot 4 of the cScriptHost table at +0x1C (0x823EB508; RuffKing's cAiPlayer::RetName returns
//     m_pAIEntity's name); ShouldTriggerFootStepEvent and ShouldTriggerBulletSoundEvent are primary slots 112 and 113
//     (see CHARACTER/cCharacterInterface.h). Slot 125 (0x823E92B8) is the first virtual cAiPlayer adds (cCharacterEntityIF's
//     primary vtable has 125 slots); RuffKing's and Burn's cAiPlayer have no counterpart, so SetFields4F8 is ours.
//   - cAiPlayerPrototype: MakeNew (0x823E78A8) builds it on GOM::cObjectPrototype's constructor and installs the vtable
//     0x820FB0BC; its slot 5, CAttributeHandler::Init(const CAttributePacket &), is 0x823EB490, which returns Ret_OK.
#ifndef AI_CAIPLAYER_H
#define AI_CAIPLAYER_H

#include "AI/cCharacterEntityIF.h"
#include "AI/AIDamageCache.h"
#include "gom/object_prototype.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "cd2/layout.h"

namespace AI
{
    class cAiPlayer : public cCharacterEntityIF
    {
    public:
        // CD2 0x823E7950 placement-constructs this class through 0x823E8650.
        cAiPlayer();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        class cAiPlayerPrototype : public GOM::cObjectPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &attr);
        };

        enum etMapStatus
        {
            kMS_Passive = 0,
            kMS_Priority,
            kMS_HighPriority,
            kMS_VeryHighPriority,
            kMS_Num
        };

        static const Fun_Runtime::cClass *ms_pcAiPlayerClass;

    private:
        AIDamageCache m_DamageCache;                            // 0x540
        unsigned char m_pad5A0[0x5D8 - 0x5A0];
        Fun_Runtime::cSafeDeletablePointerBase m_pOwnedVehicle; // 0x5D8 (object pointer at 0x5E4)
        unsigned char m_pad5E8[0x5F8 - 0x5E8];
        float m_fFriendlyFireTolerance;                         // 0x5F8
        float m_fCombatFriendlyFireTolerance;                   // 0x5FC
        unsigned char m_pad600[0x60C - 0x600];
        etMapStatus m_nMapStatus;                               // 0x60C
        unsigned char m_pad610[0x614 - 0x610];
        short m_nShotsRemaining;                                // 0x614
        bool m_bInterestingObjectReactionEnabled;               // 0x616
        unsigned char m_nInterestingObjectPriority;             // 0x617
        unsigned char m_pad618[0x620 - 0x618];

    protected:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
    public:
        virtual const char *RetName() const;
        virtual bool ShouldTriggerFootStepEvent();
        virtual bool ShouldTriggerBulletSoundEvent();
        virtual void SetFields4F8(int v, int w);

        void SetMapStatus(unsigned int nMapStatus);
        void SetFriendlyFireTolerance(float fTolerance);
        void SetCombatFriendlyFireTolerance(float fTolerance);
        void SetShotsRemaining(short nShots);
        bool IsInterestingObjectReactionEnabled() const;
        void SetInterestingObjectReactionEnabled(bool bEnabled);
        unsigned char RetInterestingObjectPriority() const;
        void SetInterestingObjectPriority(unsigned char nPriority);
        cNonGameBase *RetOwnedVehicle() const;
        float RecallDamageCaused(CHARACTER::cCharacter *pCharacter);

        // Not cAiPlayer's (see src/AI/cAiPlayer.cpp): kept here under their old names until their classes are known.
        static int RetConstantC8();
        const char *RetTriggerEventFlags() const;
        const char *RetEnemyStatus() const;
        const char *RetMapStatus() const;
        void *GetField60() const;
        void *GetField50() const;

        CD2_LAYOUT_CHECKS(cAiPlayer,
            CD2_SIZE(cAiPlayer, 0x620)
            CD2_OFFSET(cAiPlayer, m_DamageCache, 0x540)
            CD2_OFFSET(cAiPlayer, m_pOwnedVehicle, 0x5D8)
            CD2_OFFSET(cAiPlayer, m_fFriendlyFireTolerance, 0x5F8)
            CD2_OFFSET(cAiPlayer, m_fCombatFriendlyFireTolerance, 0x5FC)
            CD2_OFFSET(cAiPlayer, m_nMapStatus, 0x60C)
            CD2_OFFSET(cAiPlayer, m_nShotsRemaining, 0x614)
            CD2_OFFSET(cAiPlayer, m_bInterestingObjectReactionEnabled, 0x616)
            CD2_OFFSET(cAiPlayer, m_nInterestingObjectPriority, 0x617))
    };
}

#endif // AI_CAIPLAYER_H
