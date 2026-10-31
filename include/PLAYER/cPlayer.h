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
        unsigned char m_pad540[0x858 - 0x540];
        unsigned int m_nAutomaticAIBreakoutFlags; // 0x858
        unsigned char m_pad85C[0xD90 - 0x85C];
    protected:
        bool m_bIsAIActive;         // 0xD90
        bool m_bIsAITargeting;      // 0xD91
        bool m_bAutomaticAIBreakout; // 0xD92
    private:
        unsigned char m_padD93[0xDC0 - 0xD93];
    protected:
        char m_strName[255]; // 0xDC0; RuffKing name and size, CD2 RetName address adjusted from cScriptHost
    private:
        unsigned char m_padEBF[0xF18 - 0xEBF];
        void *m_pCamera; // 0xF18, returned by the script method RetCameraPtr
        unsigned char m_padF1C[0x1160 - 0xF1C];

    public:
        // CD2's prototype allocation is 0x70 bytes; its slot 5 (0x82725740) is Init, as in RuffKing.
        class cPlayerPrototype : public GOM::cObjectPrototype
        {
        public:
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
        void SetAITargeting(bool bAITargeting);

        CD2_LAYOUT_CHECKS(cPlayer,
            CD2_SIZE(cPlayer, 0x1160)
            CD2_OFFSET(cPlayer, m_bIsAIActive, 0xD90)
            CD2_OFFSET(cPlayer, m_bIsAITargeting, 0xD91)
            CD2_OFFSET(cPlayer, m_bAutomaticAIBreakout, 0xD92)
            CD2_OFFSET(cPlayer, m_nAutomaticAIBreakoutFlags, 0x858)
            CD2_OFFSET(cPlayer, m_strName, 0xDC0)
            CD2_OFFSET(cPlayer, m_pCamera, 0xF18))
    };
}

#endif // PLAYER_CPLAYER_H
