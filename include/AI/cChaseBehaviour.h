// AI::cChaseBehaviour (CD2 layout, 0x100 bytes) and its prototype.
// Layout from F31 (ctor): the base NPCBehaviourSM (out-of-line ctor 0x824ABA30, whose chain reaches cNonGameBase's
// constructor) is a cNonGameBase (gom/non_game_base.h, 0x7C bytes) plus its own fields to 0xD0; own fields from 0xD0.
// Primary vtable (0x8210BCA8) has 119 slots: 0..67 are cNonGameBase's (11 RetClassName), 68..118 NPCBehaviourSM's and
// cChaseBehaviour's. RetClass and IsA are in the cRegisteredClass vtable (0x8210BE84, right after the primary).
// Stand-ins (all ours, sized/slotted to CD2): AI::NPCBehaviourSM, AI::NPCHost (the character at this+0x7C) and
// AI::NPCBehaviourPrototype (a GOM::cObjectPrototype, size 0x90; two out-of-line HandleAttributes base calls: in
// RuffKing NPCBehaviourPrototype::HandleAttributes calls its base's HandleAttributes and SetupArmoury, inlined in CD2).
#ifndef AI_CCHASEBEHAVIOUR_H
#define AI_CCHASEBEHAVIOUR_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "gom/non_game_base.h"

namespace AI
{
    struct TargetInfo { unsigned int v[4]; };
    class TgtSubA { public: virtual void A0(); virtual void A1(); virtual void A2(); virtual TargetInfo GetInfo(); unsigned char pad[0x10]; };
    class TgtReg { public: virtual void R0(); virtual bool IsA(const Fun_Runtime::cClass &) const; unsigned char pad[4]; };
    class TgtBase0
    {
    public:
        virtual void T0();
        virtual void T1();
        virtual void T2();
        virtual void T3();
        virtual void T4();
        virtual void T5();
        virtual void T6();
        virtual void T7();
        virtual void T8();
        virtual void T9();
        virtual void T10();
        virtual void T11();
        virtual void T12();
        virtual void T13();
        virtual void T14();
        virtual void T15();
        virtual void T16();
        virtual void T17();
        virtual void T18();
        virtual void T19();
        virtual void T20();
        virtual void T21();
        virtual void T22();
        virtual void T23();
        virtual void T24();
        virtual void T25();
        virtual void T26();
        virtual void T27();
        virtual void T28();
        virtual void T29();
        virtual void T30();
        virtual void T31();
        virtual void T32();
        virtual void T33();
        virtual void T34();
        virtual void T35();
        virtual void T36();
        virtual void T37();
        virtual void T38();
        virtual void T39();
        virtual void T40();
        virtual void T41();
        virtual void T42();
        virtual void T43();
        virtual void T44();
        virtual void T45();
        virtual void T46();
        virtual void T47();
        virtual void T48();
        virtual bool IsAliveLike();
        unsigned char pad[0x1C - 4];
    };
    // Stand-in for the chase target (a character): primary vtable (49+ slots), a sub-object at 0x1C and a
    // registered-class sub-object at 0x30.
    class NPCTarget : public TgtBase0, public TgtSubA, public TgtReg { public: unsigned char pad2[0x20]; };

    struct HostReg { unsigned char pad[0x37]; bool m_b37; bool m_b38; };
    struct NPCRegistry { unsigned char pad[4]; HostReg *m_pReg; unsigned char pad2[0x50 - 8]; };

    // ---- Stand-ins for the owning character's object graph (offsets from F34..F40). Each "Sub" is a polymorphic base
    // sub-object at 0x1C of its complete class (pointers to it are adjusted by -0x1C with static_cast).
    struct Pre1C { virtual void Pre0(); unsigned char pad[0x18]; };
    struct PlayerSub { virtual void PS0(); };
    struct XSub { virtual void XS0(); };
    struct YSub { virtual void YS0(); };
    struct Obj1524 { virtual void O0(); virtual void O1(); virtual void O2(); virtual void O3(); virtual unsigned int O4(); virtual unsigned int O5(); };

    struct YBase
    {
        virtual void Y0();
        virtual void Y1();
        virtual void Y2();
        virtual void Y3();
        virtual void Y4();
        virtual void Y5();
        virtual void Y6();
        virtual void Y7();
        virtual void Y8();
        virtual void Y9();
        virtual void Y10();
        virtual void Y11();
        virtual void Y12();
        virtual void Y13();
        virtual void Y14();
        virtual void Y15();
        virtual void Y16();
        virtual void Y17();
        virtual void Y18();
        virtual void Y19();
        virtual void Y20();
        virtual void Y21();
        virtual void Y22();
        virtual void Y23();
        virtual void Y24();
        virtual void Y25();
        virtual void Y26();
        virtual void Y27();
        virtual void Y28();
        virtual void Y29();
        virtual void Y30();
        virtual void Y31();
        virtual void Y32();
        virtual void Y33();
        virtual void Y34();
        virtual void Y35();
        virtual void Y36();
        virtual void Y37();
        virtual void Y38();
        virtual void Y39();
        virtual void Y40();
        virtual void Y41();
        virtual void Y42();
        virtual void Y43();
        virtual void Y44();
        virtual void Y45();
        virtual void Y46();
        virtual void Y47();
        virtual void Y48();
        virtual void Y49();
        virtual void Y50();
        virtual void Y51();
        virtual void Y52();
        virtual void Y53();
        virtual void Y54();
        virtual void Y55();
        virtual void Y56();
        virtual void Y57();
        virtual void Y58();
        virtual void Y59();
        virtual void Y60();
        virtual void Y61();
        virtual void Y62();
        virtual void Y63();
        virtual void Y64();
        virtual void Y65();
        virtual void Y66();
        virtual void Y67();
        virtual void Y68();
        virtual void Y69();
        virtual void Y70();
        virtual void Y71();
        virtual void Y72();
        virtual void Y73();
        virtual void Y74();
        virtual void Y75();
        virtual void SetV(float);
        virtual float GetV();
        unsigned char pad[0x18];
    };
    class Y : public YBase, public YSub
    {
    public:
        unsigned char padY[0x820 - 0x20];
        int m_n820;
        int m_n824;
    };
    class X : public Pre1C, public XSub
    {
    public:
        unsigned char padX[0xD14 - 0x20];
        YSub *m_pY;
    };
    class Player : public Pre1C, public PlayerSub
    {
    public:
        unsigned char padP[0x1524 - 0x20];
        Obj1524 *m_p1524;
        unsigned char padP2[0x1700 - 0x1528];
        XSub *m_pX;
    };

    struct HostLinks { unsigned char pad[0xC]; PlayerSub *m_pPlayerSub; };   // at host+0x7C; m_pPlayerSub is host+0x88
    // The character that owns the behaviour (this+0x7C). Only offsets used here.
    struct NPCHost : public TgtBase0
    {
        unsigned char pad0[0x7C - sizeof(TgtBase0)];
        HostLinks m_Links;     // 0x7C

        unsigned char pad8C[0x4E0 - 0x7C - sizeof(HostLinks)];
        NPCRegistry m_Registry;
        unsigned char padReg[3];
        unsigned char m_nMode;   // 0x533
    };

    class NPCBehaviourSM : public cNonGameBase
    {
    public:
        NPCBehaviourSM();
        virtual const char *RetClassName() const;
        virtual void OnEnter();
        virtual void OnExit();
        virtual void Slot70();
        virtual void Slot71();
        virtual void Slot72();
        virtual void Slot73();
        virtual void OnEvent74(NPCTarget *t);
        virtual void OnEvent75(NPCTarget *t);
        virtual void Slot76();
        virtual void Slot77();
        virtual void Slot78();
        virtual void Slot79();
        virtual void Slot80();
        virtual void Slot81();
        virtual void Slot82();
        virtual void Slot83();
        virtual void Slot84();
        virtual void Slot85();
        virtual void Slot86();
        virtual void Slot87();
        virtual void Slot88();
        virtual void Slot89();
        virtual void Slot90();
        virtual void Slot91();
        virtual void Slot92();
        virtual void Slot93();
        virtual void Slot94();
        virtual void Slot95();
        virtual void Update(float dt);
        virtual void Slot97();
        virtual void V98();
        virtual void SetState(int n);
        virtual void GetState(int n);
        virtual void Slot101();
        virtual void V102();
        virtual void Slot103();
        virtual void V104();
        virtual void Slot105();
        virtual void V106();
        virtual void V107();
        virtual void V108();
        virtual void Slot109();
        virtual void Slot110();
        virtual void V111(float dt);
        virtual void Slot112();
        virtual void Slot113();
        virtual void Slot114();
        virtual NPCTarget *GetTarget();
        virtual int GetTargetId();
        virtual void V117();
        virtual void V118();
        NPCHost *m_pHost;         // 0x7C
        unsigned char pad80[0xA8 - 0x80];
        int m_nState;             // 0xA8
        unsigned char padAC[4];
        float m_fTimer;           // 0xB0
        void *m_pB4;              // 0xB4
        unsigned char padB8[0xC4 - 0xB8];
        bool m_bC4;
        unsigned char padC5[0xD0 - 0xC5];
    };

    class NPCBehaviourPrototype : public GOM::cObjectPrototype
    {
    public:
        NPCBehaviourPrototype(const RWS::CAttributePacket &);
        void HandleAttributesBase(const RWS::CAttributePacket &);
        void HandleAttributesNPC(const RWS::CAttributePacket &);
        unsigned char pad[0x90 - 0x70];
    };

    class cChaseBehaviour : public NPCBehaviourSM
    {
    public:
        class cChaseBehaviourPrototype : public NPCBehaviourPrototype
        {
        public:
            __forceinline cChaseBehaviourPrototype(const RWS::CAttributePacket &packet) : NPCBehaviourPrototype(packet) {}
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cChaseBehaviourPrototype,
                CD2_SIZE(cChaseBehaviourPrototype, 0x90))
        };

        unsigned int m_hD0;               // 0xD0 handle (zero when none)
        float m_fD4;              // 0xD4 timer
        unsigned char padD8[0xE0 - 0xD8];
        struct Vec3 { float x, y, z; Vec3() : x(0.0f), y(0.0f), z(0.0f) {} } m_vTarget;       // 0xE0
        unsigned char padEC[4];
        int m_nF0;                // 0xF0 handle, -1 when none
        bool m_bF4;
        bool m_bF5;
        bool m_bF6;
        unsigned char padF7[9];

        static Fun_Runtime::cClass *const ms_pcChaseBehaviourClass;
        static const char *const pcChaseBehaviourClassID;

        cChaseBehaviour();
        virtual const char *RetClassName() const;

        virtual void OnEnter();
        virtual void OnExit();
        virtual void OnEvent74(NPCTarget *t);
        virtual void OnEvent75(NPCTarget *t);
        void SetTarget(NPCTarget *t);
        bool TryBindTarget();
        virtual void Update(float dt);
        virtual void GetState(int n);
        virtual void V102();
        virtual void V104();
        virtual void V106();
        virtual void V107();
        virtual void V108();
        virtual void V111(float dt);
        virtual void V117();
        virtual void V118();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual void Slot2();     // cSafeDeletable slot 2: cChaseBehaviour's own (0x824CE808, not yet matched)

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(void *proto, void *mem);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cChaseBehaviour,
            CD2_SIZE(cChaseBehaviour, 0x100)
            CD2_OFFSET(cChaseBehaviour, m_hD0, 0xD0)
            CD2_OFFSET(cChaseBehaviour, m_nF0, 0xF0))
    };
}

#endif
