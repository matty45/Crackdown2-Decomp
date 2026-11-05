// PLAYER::cPlayer (Crackdown 2): STAND-IN, sized to CD2; only what matched code needs, the rest is padding. Evidence:
//   - Size 0x1160: StaticCreateClass 0x8271F198 builds cClass(4, "cPlayer", 0x1160). RuffKing's cPlayer (0x680 bytes)
//     is laid out differently.
//   - Bases: AI::cCharacterEntityIF first, as in RuffKing. The other bases start at 0x540 (the constructor 0x8271F7C8
//     stores vptrs at 0x540, 0x544 and 0x548; RuffKing: GDb::cDebugPageHandler, SaveGame::cLoadSaveObject,
//     cPlayerSystemInterface) and are not modelled: padding.
//   - m_bIsAIActive (0xD90; RuffKing's name) and m_bIsAITargeting (0xD91; the name is ours, after the script method):
//     cPlayer's script methods (registered in 0x8271F230) are "SetAIActive" (0x82724980: stores 0xD90, then re-applies
//     SetAITargeting with 0xD91), "IsAIActive" (0x82724990: returns 0xD90), "SetAITargeting" (0x82724998: stores 0xD91)
//     and "IsAITargeting" (0x82724A28: returns 0xD91). RuffKing has m_bIsAIActive only.
//   - Script methods "Set/IsAutomaticAIBreakout" (0x82724B40/0x82724B50) access 0xD92;
//     "RetAutomaticAIBreakoutFlags" (0x82724B58) reads the word at 0x858. The field names
//     follow the script names; their offsets are confirmed by these CD2 functions.
//   - RetName (0x82724808) is slot 4 of the cScriptHost vtable at +0x1C and returns this+0xDA4. RuffKing's
//     cPlayer::RetName returns m_strName, a 255-byte buffer at 0x41E; the CD2 buffer is at 0xDC0 after the +0x1C
//     subobject adjustment.
//   - Primary vtable 0x8200C0E0 (installed by the constructor): slots 112 and 113 are ShouldTriggerFootStepEvent
//     (0x82725750, true while the character's LOD level is at most 1) and ShouldTriggerBulletSoundEvent (0x82725780,
//     a 1 s interval), the slots cAiPlayer's overrides have; RuffKing's and Burn's cPlayer override both. Slot 94
//     (0x82720FD0) is HasRecentlyHadH2HContact by its code (RuffKing's m_nH2HContactFrame test). Slot 97 (GetByteD99,
//     0x8271F160) and slot 130 (ResetFloatEC4, 0x82720AC0, the 5th virtual cPlayer adds) have no reference counterpart.
#ifndef PLAYER_CPLAYER_H
#define PLAYER_CPLAYER_H

#include "AI/cCharacterEntityIF.h"
#include "CHARACTER/cCwTransCharacterWrapper.h"
#include "cd2/layout.h"

namespace PLAYER
{
    class cPlayer : public AI::cCharacterEntityIF
    {
    private:
        unsigned char m_pad540[0x7E4 - 0x540];
        // CD2 ForceCharacterH2HContact/HasRecentlyHadH2HContact (0x82720FC0/0x82720FD0);
        // RuffKing names the saved game-tick count m_nH2HContactFrame.
        unsigned int m_nH2HContactFrame;
        unsigned char m_pad7E8[0x858 - 0x7E8];
        unsigned int m_nAutomaticAIBreakoutFlags; // 0x858
        unsigned char m_pad85C[0xD90 - 0x85C];
    protected:
        bool m_bIsAIActive;         // 0xD90
        bool m_bIsAITargeting;      // 0xD91
        bool m_bAutomaticAIBreakout; // 0xD92
    private:
        unsigned char m_padD93[0xD99 - 0xD93];
        unsigned char m_byteD99; // 0xD99
        unsigned char m_padD9A[0xDC0 - 0xD9A];
    protected:
        char m_strName[255]; // 0xDC0; RuffKing name and size, CD2 RetName address adjusted from cScriptHost
    private:
        unsigned char m_padEBF[0xEC4 - 0xEBF];
        float m_fEC4; // 0xEC4
        unsigned char m_padEC8[0xF18 - 0xEC8];
        void *m_pCamera; // 0xF18, returned by the script method RetCameraPtr
        unsigned char m_padF1C[0x1160 - 0xF1C];

    public:
        // CD2 0x8271F140: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2's prototype allocation is 0x70 bytes; its slot 5 (0x82725740) is Init, as in RuffKing. Base as in RuffKing.
        // MakeNew (0x8271F0A8) calls GOM::cObjectPrototype's constructor with the packet and installs the vtables
        // 0x8213D518 (at 0) and 0x821327A4 (at 0x18, shared by every prototype).
        class cPlayerPrototype : public AI::cCharacterEntityIF::cCharacterEntityIFPrototype
        {
        public:
            // __forceinline: CD2 inlines the constructor chain into MakeNew (as cCharacterInterfacePrototype's).
            __forceinline cPlayerPrototype(const RWS::CAttributePacket &packet)
                : AI::cCharacterEntityIF::cCharacterEntityIFPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cPlayerPrototype,
                CD2_SIZE(cPlayerPrototype, 0x70))
        };
        static const Fun_Runtime::cClass *ms_pcPlayerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        virtual const char *RetName() const;
        virtual const char *RetClassName() const;
        void SetAIActive(bool active);
        bool IsAIActive() const;
        bool IsAITargeting() const;
        void SetAutomaticAIBreakout(bool enabled, unsigned int flags);
        bool IsAutomaticAIBreakout() const;
        int RetAutomaticAIBreakoutFlags() const;
        void *RetCameraPtr() const;
        unsigned char GetByteD99() const;
        bool ShouldTriggerBulletSoundEvent();
        bool ShouldTriggerFootStepEvent();
        void ResetFloatEC4();
        void SetAITargeting(bool bAITargeting);
        void ForceCharacterH2HContact();
        bool HasRecentlyHadH2HContact();

        CD2_LAYOUT_CHECKS(cPlayer,
            CD2_SIZE(cPlayer, 0x1160)
            CD2_OFFSET(cPlayer, m_nH2HContactFrame, 0x7E4)
            CD2_OFFSET(cPlayer, m_bIsAIActive, 0xD90)
            CD2_OFFSET(cPlayer, m_bIsAITargeting, 0xD91)
            CD2_OFFSET(cPlayer, m_bAutomaticAIBreakout, 0xD92)
            CD2_OFFSET(cPlayer, m_nAutomaticAIBreakoutFlags, 0x858)
            CD2_OFFSET(cPlayer, m_strName, 0xDC0)
            CD2_OFFSET(cPlayer, m_byteD99, 0xD99)
            CD2_OFFSET(cPlayer, m_fEC4, 0xEC4)
            CD2_OFFSET(cPlayer, m_pCamera, 0xF18))
    };
}

#endif // PLAYER_CPLAYER_H
