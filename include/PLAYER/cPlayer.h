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
//     (0x82720FD0) is HasRecentlyHadH2HContact by its code (RuffKing's m_nH2HContactFrame test), slot 92 (0x82720FC0)
//     ForceCharacterH2HContact. Slot 97 (0x8271F160, reads m_byteD99) and slot 130 (0x82720AC0, clears m_fEC4, the 5th
//     virtual cPlayer adds) have no reference counterpart. None of these slots is declared yet, so they are open.
// Known wrong, left for a structural fix: CD2 also registers cPlayer under GDb::cDebugPageHandler (inheritance registrar 0x82FF3C60), one
// of the bases whose vptrs the constructor stores at 0x540-0x548. The padding there stands in for those bases.
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
        bool m_byteD99; // 0xD99: a flag (slot 97 returns it as bool)
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
        // CD2 primary slot 18 overrides the character-interface initializer.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);

        // CD2 0x8271F140: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // The body (0x823B7ED8) lies in the order-list region; its deleting wrapper (0x8271FE70) calls it.
        virtual ~cPlayer();
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
        // RuffKing's name; CD2 0x83800F88, read by cTacticalObjective::IsLocalPlayerNearby (0x82478A80).
        static cPlayer *g_pLocalPlayer;
        // RuffKing's name; inline in CD2 (cBreachHoleMission::IsLocalPlayerNearby 0x82473330 expands it). It converts
        // the typed safe pointer directly: one null test before the 0x1C adjustment, where RetCharacter's conditional
        // adds a register copy.
        static CHARACTER::cCharacter *RetLocalPlayerCharacter()
        {
            if (g_pLocalPlayer)
                return g_pLocalPlayer->m_pCharacter;
            return 0;
        }
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

        // Primary-table overrides (table 0x8200C0E0): slots 92, 94, 112 and 113.
        virtual void ForceCharacterH2HContact();
        virtual bool HasRecentlyHadH2HContact();
        virtual bool ShouldTriggerFootStepEvent();
        virtual bool ShouldTriggerBulletSoundEvent();
        virtual bool vf97();     // slot 97 (0x8271F160): returns m_byteD99; no reference name

        // cPlayer's own primary slots 125..138 (table 0x8200C0E0 has 139 entries; cCharacterEntityIF ends at 124).
        // Unnamed slots keep their index; 125, 127 and 129 are bodies in the order-list region.
        virtual void vf125();
        virtual void vf126();
        virtual void vf127();
        virtual void vf128();
        virtual void vf129();
        virtual void vf130();    // 0x82720AC0: clears m_fEC4
        virtual void vf131();    // 0x82720B88: as authority, debounces GA_CHARACTER_OBJECTDROP
        virtual void vf132();
        virtual void vf133();
        virtual void vf134();    // 0x82720D70: as authority, debounces GA_CHARACTER_OBJECTINTERACT

        // CD2: cPlayer's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8237D410
        virtual bool EnterPhysicalState(); // 7: 0x821EE6B8
        virtual void Slot22(); // 22: 0x82723D50
        virtual void Slot23(); // 23: 0x82723E80
        virtual void Slot24(); // 24: 0x82723E38
        virtual void Slot51(); // 50: 0x82721230
        virtual void vf69(); // 69: 0x827240B8
        virtual void vf73(); // 73: 0x82720DC8
        virtual void vf74(); // 74: 0x823EFCD8
        virtual void vf77(); // 77: 0x8271FEC0
        virtual void vf78(); // 78: 0x82721AD8
        virtual void vf82(); // 82: 0x827205C8
        virtual void vf83(); // 83: 0x82386D18
        virtual void vf84(); // 84: 0x823EF930
        virtual void vf85(); // 85: 0x827203F0
        virtual void vf86(); // 86: 0x82720FF0
        virtual void vf93(); // 93: 0x822E6700
        virtual void vf108(); // 108: 0x8232F958
        virtual void vf109(); // 109: 0x82399A88
        virtual void vf115(); // 115: 0x827219D0
        virtual void vf121(); // 121: 0x8237D1E0
        virtual void vf124(); // 124: 0x82723C80
        virtual void Slot2(); // cSafeDeletable 2: 0x82724A30
    public:
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

    public:
        // CD2 table 0x8200C0E0 differs from cCharacterEntityIF at these inherited slots.
        virtual void vf116(); // slot 116: 0x821F5B18
        virtual void vf117(); // slot 117: 0x82724990
    };
}

#endif // PLAYER_CPLAYER_H
