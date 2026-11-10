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
//   - g_cAiPlayer is named after the type it is registered as: CD2's initializers (0x82F605D0 and others) pass the
//     global, a name and its parent's name to 0x82772828 ("cAIPlayer" under "cCharacterEntityIF", "AIE_SHOTS_COUNTER"
//     under "AIEvent"). RetScriptTypeRegistration (0x823E7978) returns it: slot 1 of the cScriptHost table at +0x1C
//     (0x82001798, whose slot 4 is RetName). The getters next to it that return the AIE_* registrars (0x823E7AA0..
//     0x823E7C08) are slot 1 of the AIE event classes' own tables (0x823E7AA0: 0x820FB114), installed by those classes'
//     constructors: not cAiPlayer's, and open until the event classes are modelled.
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

namespace Vehicle { class cVehicle; }

namespace AI
{
    class cAiPlayer;

    // What the cAiPlayer constructor (0x823E8650) calls after its fields. Nothing in CD2 or the reference builds names
    // these; the names are ours, from their addresses:
    //   - Ext_82223708(type, owner) returns whether the per-type list at 0x83A023C8 holds an entry for owner;
    //   - Ext_82887CB8(type, object) adds object to the per-type lists at 0x83A01CBC and 0x83A023C8;
    //   - cUnknown828891A0 is the 0x280-byte object the constructor registers under type 0x18 (its constructor,
    //     0x828891A0, stores the owner at 0x27C);
    //   - Ext_828396F8 is called with the address of a copy of `this` while the counter g_838015E0 is raised.
    class cUnknown828891A0
    {
    public:
        explicit cUnknown828891A0(cAiPlayer *pOwner);

    private:
        unsigned char m_pad[0x280];
    };
    bool Ext_82223708(int nType, cNonGameBase *pOwner);
    void Ext_82887CB8(int nType, cUnknown828891A0 *pObject);
    void Ext_828396F8(cAiPlayer *const &pPlayer);
    extern int g_838015E0;

    class cAiPlayer : public cCharacterEntityIF
    {
    public:
        // CD2 0x823E7950 placement-constructs this class through 0x823E8650.
        cAiPlayer();
        // The body (0x822FFE70) lies in the order-list region; its deleting wrapper (0x823E87F8) calls it.
        virtual ~cAiPlayer();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        class cAiPlayerPrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (0x823E78A8), which allocates 0x90 bytes and
            // initialises the fields below (names ours) after the vtables.
            __forceinline cAiPlayerPrototype(const RWS::CAttributePacket &packet)
                : GOM::cObjectPrototype(packet), m_nUnknown70(0), m_nUnknown74(0), m_nUnknown78(3),
                  m_bUnknown7C(true), m_bUnknown7D(false), m_nUnknown80(0) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &attr);

        private:
            unsigned int m_nUnknown70; // 0x70
            unsigned int m_nUnknown74; // 0x74
            unsigned int m_nUnknown78; // 0x78
            bool m_bUnknown7C;         // 0x7C
            bool m_bUnknown7D;         // 0x7D
            unsigned int m_nUnknown80; // 0x80
            // 0x84-0x90: tail padding (GOM::cObjectPrototype is 16-byte aligned).

            // CD2: cAiPlayerPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x823EB318
        private:
            CD2_LAYOUT_CHECKS(cAiPlayerPrototype,
                CD2_SIZE(cAiPlayerPrototype, 0x90)
                CD2_OFFSET(cAiPlayerPrototype, m_nUnknown70, 0x70))
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
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // The constructor (0x823E8650) zeroes 0x5A0..0x5D4 word by word, builds the two safe pointers, and sets the
        // floats to 0.3, 1.0, 20.0, 20.0 and 0.0, then 0x60C..0x61B; the unnamed fields' names are ours.
        AIDamageCache m_DamageCache;                            // 0x540
        unsigned int m_nUnknown5A0;
        unsigned int m_nUnknown5A4;
        unsigned int m_nUnknown5A8;
        unsigned int m_nUnknown5AC;
        unsigned int m_nUnknown5B0;
        unsigned int m_nUnknown5B4;
        unsigned int m_nUnknown5B8;
        unsigned int m_nUnknown5BC;
        unsigned int m_nUnknown5C0;
        unsigned int m_nUnknown5C4;
        unsigned int m_nUnknown5C8;
        unsigned int m_nUnknown5CC;
        unsigned int m_nUnknown5D0;
        unsigned int m_nUnknown5D4;
        // Two pointee types: CD2 builds the safe-pointer vtable address separately for each (one folded table,
        // 0x82155680). Vehicle::cVehicle is RuffKing's vehicle class; the second pointer's type is not known.
        Fun_Runtime::cSafeDeletablePointer<Vehicle::cVehicle> m_pOwnedVehicle; // 0x5D8 (object pointer at 0x5E4)
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pUnknown5E8;        // 0x5E8
        float m_fFriendlyFireTolerance;                         // 0x5F8
        float m_fCombatFriendlyFireTolerance;                   // 0x5FC
        float m_fUnknown600;
        float m_fUnknown604;
        float m_fUnknown608;
        etMapStatus m_nMapStatus;                               // 0x60C
        unsigned int m_nUnknown610;
        short m_nShotsRemaining;                                // 0x614
        bool m_bInterestingObjectReactionEnabled;               // 0x616
        unsigned char m_nInterestingObjectPriority;             // 0x617
        bool m_bUnknown618;
        bool m_bUnknown619;
        bool m_bUnknown61A;
        bool m_bUnknown61B;
        unsigned char m_pad61C[0x620 - 0x61C];

    protected:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
    public:
        // CD2 0x823E7978: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        virtual const char *RetName() const;
        // CD2 forwards these primary slots to the attached character; names remain unknown.
        // Keep the shared base's provisional identifiers: Slot54/Slot60 compile to physical slots 53/59.
        virtual void Slot20(); // 0x823EB5A8, guarded forwarding
        virtual void Slot54(); // 0x823E8A90
        virtual void Slot60(); // 0x823E7A10
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

        // Not cAiPlayer's (see src/AI/cAiPlayer.cpp): kept here under its old name until its class is known.
        static int RetConstantC8();

        // CD2: cAiPlayer's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x823E8BE8
        virtual bool EnterPhysicalState(); // 7: 0x823E8FA0
        virtual void Slot17(); // 17: 0x823E8848
        virtual void Slot21(); // 21: 0x8227FBC8
        virtual void Slot27(); // 27: 0x821D2968
        virtual void Slot63(); // 62: 0x823E7A38
        virtual void Slot64(); // 63: 0x8227FAE8
        virtual void Slot65(); // 64: 0x823E8B50
        virtual void vf69(); // 69: 0x823E8AB8
        virtual void vf73(); // 73: 0x823E92C8
        virtual void vf74(); // 74: 0x82377190
        virtual void vf77(); // 77: 0x823E9040
        virtual void vf78(); // 78: 0x823867E0
        virtual void vf79(); // 79: 0x823A04A0
        virtual void vf84(); // 84: 0x823E92B0
        virtual bool ShouldTriggerVocalEvent(); // 111: 0x8237B148
        virtual void vf114(); // 114: 0x8234B7A0
        virtual void vf116(); // 116: 0x823E8D20
        virtual void vf117(); // 117: 0x8288FB78
        virtual void Slot2(); // cSafeDeletable 2: 0x823E9FD0
    public:
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
