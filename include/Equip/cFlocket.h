// Equip::cFlocket and Equip::cFlocket::cFlocketPrototype (Crackdown 2). CD2 object size 0x9B0, prototype 0x360.
// CD2 layout, worked out from F30 (ctor), F32 (dtor), the vtable blob at 0x82126E0C.. and the adjustor thunks F47-F57:
//   0x000 cNonGameBase   (gom/non_game_base.h: CAttributeHandler, and CEventHandler 0x18, cSafeDeletable 0x1C,
//                         cRegisteredClass 0x30, cNetRoleObject 0x38; RetClassName is slot 11), to 0x7C
//   0x07C cHWProjectileBase (the rest of the chain down to cNonGameBase, to 0x120: cGameBase (0x82650610) and the
//                         equipment classes, whose constructors F30's base constructor chain runs through)
//   0x120 cRegClassB     (RetClass, IsA, dtor)       thunks -0xF0 reach the 0x30 subobject
//   0x250 cPoly250       (dtor)
//   0x294 cPoly294       (dtor)
//   0x420 cPoly420       (cPositionalProxy-like, no dtor override)
//   0x510 cRegClassC     (RetClass, IsA, 5 virtuals, dtor in slot 7)  thunks -0x4E0
//   0x870 cPoly870       (cExplosionCallback-like, to 0x970)
//   0x970 cFlocket fields (16-byte aligned Vec3s), size 0x9B0.
// Apart from cNonGameBase, the base classes up to 0x970 are STAND-INS (cHWProjectile and its bases are unknown to the
// repo): only offsets, vptr count and the virtual slots cFlocket needs are reproduced. Primary virtuals 68..372 are
// named Slot<N>.
#ifndef EQUIP_CFLOCKET_H
#define EQUIP_CFLOCKET_H

#include <ppcintrinsics.h>
#include "rws/attributes.h"
#include "rws/classfactory.h"
#include "cd2/layout.h"
#include "cd2/memory.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vec3.h"
#include "gom/non_game_base.h"

namespace Fun_Runtime
{
}

namespace Equip
{
    // ---- stand-in secondary bases of cHWProjectile ----
    class cHWProjectileBase : public cNonGameBase { public: unsigned char m_pad7C[0x120 - 0x7C]; };
    class cRegClassB
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cRegClassB();
        unsigned char m_pad[0x130 - 4];
    };
    class cPoly250 { public: virtual ~cPoly250(); unsigned char m_pad[0x40]; };
    class cPoly294 { public: virtual ~cPoly294(); unsigned char m_pad[0x188]; };
    class cPoly420 { public: virtual void Slot0(); unsigned char m_pad[0xEC]; };
    class cRegClassC
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual void Slot2();
        virtual void Slot3();
        virtual void Slot4();
        virtual void Slot5();
        virtual void Slot6();
        virtual ~cRegClassC();
        virtual void ReplicateInitialFields();   // slot 8
        virtual void ReplicateFields();          // slot 9
        void ReadVec3(Fun_Runtime::Vec3 *out, int id);   // sub_8282C160 (name ours)
        void ReadFloat(float *out, int id);              // sub_8282C0D0 (name ours)
        unsigned char m_pad0[0x84];
        unsigned char m_nUnk88;                            // read by cFlocket::ReplicateFields (== 199)
        unsigned char m_pad1[0x360 - 0x89];
    };
    class cPoly870 { public: virtual void Slot0(); unsigned char m_pad[0xFC]; };

    // Stand-in for cHWProjectile (CD2 0x970 bytes). Out-of-line ctor/dtor (F30 calls them).
    class cHWProjectile : public cHWProjectileBase, public cRegClassB, public cPoly250, public cPoly294, public cPoly420,
        public cRegClassC, public cPoly870
    {
    public:
        cHWProjectile();
        virtual ~cHWProjectile();
        virtual const char *RetClassName() const;      // slot 11
// primary virtuals 68..374 (the CD2 primary vtable has 375 slots); real names unknown except as noted in cFlocket
        virtual void Slot68();         virtual void Slot69();         virtual void Slot70();         virtual void Slot71();
        virtual void Slot72();         virtual void Slot73();         virtual void Slot74();         virtual void Slot75();         virtual void Slot76();         virtual void Slot77();
        virtual void Slot78();         virtual void Slot79();         virtual void Slot80();         virtual void Slot81();         virtual void Slot82();         virtual void Slot83();
        virtual void Slot84();         virtual void Slot85();         virtual void Slot86();         virtual void Slot87();         virtual void Slot88();         virtual void Slot89();
        virtual void Slot90();         virtual void Slot91();         virtual void Slot92();         virtual void Slot93();         virtual void Slot94();         virtual void Slot95();
        virtual void Slot96();         virtual void Slot97();         virtual void Slot98();         virtual void Slot99();         virtual void Slot100();         virtual void Slot101();
        virtual void Slot102();         virtual void Slot103();         virtual void Slot104();         virtual void Slot105();         virtual void Slot106();         virtual void Slot107();
        virtual void Slot108();         virtual void Slot109();         virtual void Slot110();         virtual void Slot111();         virtual void Slot112();         virtual void Slot113();
        virtual void Slot114();         virtual void Slot115();         virtual void Slot116();         virtual void Slot117();         virtual void Slot118();         virtual void Slot119();
        virtual void Slot120();         virtual void Slot121();         virtual void Slot122();         virtual void Slot123();         virtual void Slot124();         virtual void Slot125();
        virtual void Slot126();         virtual void Slot127();         virtual void Slot128();         virtual void Slot129();         virtual void Slot130();         virtual void Slot131();
        virtual void Slot132();         virtual void Slot133();         virtual void Slot134();         virtual void Slot135();         virtual void Slot136();         virtual void Slot137();
        virtual void Slot138();         virtual void Slot139();         virtual void Slot140();         virtual void Slot141();         virtual void Slot142();         virtual void Slot143();
        virtual void Slot144();         virtual void Slot145();         virtual void Slot146();         virtual void Slot147();         virtual void Slot148();         virtual void Slot149();
        virtual void Slot150();         virtual void Slot151();         virtual void Slot152();         virtual void Slot153();         virtual void Slot154();         virtual void Slot155();
        virtual void Slot156();         virtual void Slot157();         virtual void Slot158();         virtual void Slot159();         virtual void Slot160();         virtual void Slot161();
        virtual void Slot162();         virtual void Slot163();         virtual void Slot164();         virtual void Slot165();         virtual void Slot166();         virtual void Slot167();
        virtual void Slot168();         virtual void Slot169();         virtual void Slot170();         virtual void Slot171();         virtual void Slot172();         virtual void Slot173();
        virtual void Slot174();         virtual void Slot175();         virtual void Slot176();         virtual void Slot177();         virtual void Slot178();         virtual void Slot179();
        virtual void Slot180();         virtual void Slot181();         virtual void Slot182();         virtual void Slot183();         virtual void Slot184();         virtual void Slot185();
        virtual void Slot186();         virtual void Slot187();         virtual void Slot188();         virtual void Slot189();         virtual void Slot190();         virtual void Slot191();
        virtual void Slot192();         virtual void Slot193();         virtual void Slot194();         virtual void Slot195();         virtual void Slot196();         virtual void Slot197();
        virtual void Slot198();         virtual void Slot199();         virtual void Slot200();         virtual void Slot201();         virtual void Slot202();         virtual void Slot203();
        virtual void Slot204();         virtual void Slot205();         virtual void Slot206();         virtual void Slot207();         virtual void Slot208();         virtual void Slot209();
        virtual void Slot210();         virtual void Slot211();         virtual void Slot212();         virtual void Slot213();         virtual void Slot214();         virtual void Slot215();
        virtual void Slot216();         virtual void Slot217();         virtual void Slot218();         virtual void Slot219();         virtual void Slot220();         virtual void Slot221();
        virtual void Slot222();         virtual void Slot223();         virtual void Slot224();         virtual void Slot225();         virtual void Slot226();         virtual void Slot227();
        virtual void Slot228();         virtual void Slot229();         virtual void Slot230();         virtual void Slot231();         virtual void Slot232();         virtual void Slot233();
        virtual void Slot234();         virtual void Slot235();         virtual void Slot236();         virtual void Slot237();         virtual void Slot238();         virtual void Slot239();
        virtual void Slot240();         virtual void Slot241();         virtual void Slot242();         virtual void Slot243();         virtual void Slot244();         virtual void Slot245();
        virtual void Slot246();         virtual void Slot247();         virtual void Slot248();         virtual void Slot249();         virtual void Slot250();         virtual void Slot251();
        virtual void Slot252();         virtual void Slot253();         virtual void Slot254();         virtual void Slot255();         virtual void Slot256();         virtual void Slot257();
        virtual void Slot258();         virtual void Slot259();         virtual void Slot260();         virtual void Slot261();         virtual void Slot262();         virtual void Slot263();
        virtual void Slot264();         virtual void Slot265();         virtual void Slot266();         virtual void Slot267();         virtual void Slot268();         virtual void Slot269();
        virtual void Slot270();         virtual void Slot271();         virtual void Slot272();         virtual void Slot273();         virtual void Slot274();         virtual void Slot275();
        virtual void Slot276();         virtual void Slot277();         virtual void Slot278();         virtual void Slot279();         virtual void Slot280();         virtual void Slot281();
        virtual void Slot282();         virtual void Slot283();         virtual void Slot284();         virtual void Slot285();         virtual void Slot286();         virtual void Slot287();
        virtual void Slot288();         virtual void Slot289();         virtual void Slot290();         virtual void Slot291();         virtual void Slot292();         virtual void Slot293();
        virtual void Slot294();         virtual void Slot295();         virtual void Slot296();         virtual void Slot297();         virtual void Slot298();         virtual void Slot299();
        virtual void Slot300();         virtual void Slot301();         virtual void Slot302();         virtual void Slot303();         virtual void Slot304();         virtual void Slot305();
        virtual void Slot306();         virtual void Slot307();         virtual void Slot308();         virtual void Slot309();         virtual void Slot310();         virtual void Slot311();
        virtual void Slot312();         virtual void Slot313();         virtual void Slot314();         virtual void Slot315();         virtual void Slot316();         virtual void Slot317();
        virtual void Slot318();         virtual void Slot319();         virtual void Slot320();         virtual void Slot321();         virtual void Slot322();         virtual void Slot323();
        virtual void Slot324();         virtual void Slot325();         virtual void Slot326();         virtual void Slot327();         virtual void Slot328();         virtual void Slot329();
        virtual void Slot330();         virtual void Slot331();         virtual void Slot332();         virtual void Slot333();         virtual void Slot334();         virtual void Slot335();
        virtual void Slot336();         virtual void Slot337();         virtual void Slot338();         virtual void Slot339();         virtual void Slot340();         virtual void Slot341();
        virtual void Slot342();         virtual void Slot343();         virtual void Slot344();         virtual void Slot345();         virtual void Slot346();         virtual void Slot347();
        virtual void Slot348();         virtual void Slot349();         virtual void Slot350();         virtual void Slot351();         virtual void Slot352();         virtual void Slot353();
        virtual void Slot354();         virtual void Slot355();         virtual void Slot356();         virtual void Slot357();         virtual void Slot358();         virtual void Slot359();
        virtual void Slot360();         virtual void Slot361();         virtual void Slot362();         virtual void Slot363();         virtual void Slot364();         virtual void Slot365();
        virtual void Slot366();         virtual void Slot367();         virtual void Slot368();         virtual void Slot369();         virtual void Slot370();         virtual void Slot371();
        virtual void Slot372();         virtual void UpdateAttachedEffect();         virtual void ReleaseEffect();
    };

    // ---- prototype side ----
    // Stand-in for cHWProjectilePrototype (CD2 0x320 bytes): a GOM::cObjectPrototype (its constructor chain reaches
    // 0x82654118) with out-of-line constructor, destructor and HandleAttributes.
    class cHWProjectilePrototype : public GOM::cObjectPrototype
    {
    public:
        cHWProjectilePrototype(const RWS::CAttributePacket &);
        virtual ~cHWProjectilePrototype();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        unsigned char m_pad[0x320 - 0x70];
    };

    class cFlocket : public cHWProjectile
    {
    public:
        Fun_Runtime::Vec3 m_vecTargetPos;     // 0x970
        float m_fFlightTime;                  // 0x980
        Fun_Runtime::Vec3 m_vMovementHint;    // 0x990
        float m_fVertAcc;                     // 0x9A0
        float m_fHorizAcc;                    // 0x9A4
        void *m_pFlockLight;                  // 0x9A8 (VFX::cGlobalLight *)

        static const Fun_Runtime::cClass *ms_pcFlocketClass;
        static const char *const pcFlocketClassID;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void UpdateAttachedEffect();
        virtual void ReleaseEffect();
        virtual void ReplicateInitialFields();
        virtual void ReplicateFields();
        void UpdateFlocketLight();
        void DestroyFlocketLight();

        cFlocket();
        virtual ~cFlocket();

        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        CD2_LAYOUT_CHECKS(cFlocket,
            CD2_SIZE(cFlocket, 0x9B0)
            CD2_OFFSET(cFlocket, m_vecTargetPos, 0x970)
            CD2_OFFSET(cFlocket, m_fFlightTime, 0x980)
            CD2_OFFSET(cFlocket, m_vMovementHint, 0x990)
            CD2_OFFSET(cFlocket, m_fVertAcc, 0x9A0)
            CD2_OFFSET(cFlocket, m_pFlockLight, 0x9A8))
    };

    class cFlocketPrototype : public cHWProjectilePrototype
    {
    public:
        char m_nLightID;                  // 0x320
        float m_fLightScaleSml;           // 0x324
        float m_fLightScaleLge;           // 0x328
        float m_fLightZOffset;            // 0x32C
        float m_fLaunchOffset;            // 0x330
        float m_fVertAccMin;              // 0x334
        float m_fVertAccMax;              // 0x338
        float m_fHorizAccMin;             // 0x33C
        float m_fHorizAccMax;             // 0x340
        float m_fFlockTime;               // 0x344
        float m_fOscilFalloffTimeRecip;   // 0x348
        float m_fToTargetAcc;             // 0x34C
        float m_fVertDec;                 // 0x350
        float m_fAirDec;                  // 0x354
        float m_fHorizOscil;              // 0x358
        unsigned int m_pad35C;            // size rounded to 0x360

        cFlocketPrototype(const RWS::CAttributePacket &);
        virtual ~cFlocketPrototype() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cFlocketPrototype,
            CD2_SIZE(cFlocketPrototype, 0x360)
            CD2_OFFSET(cFlocketPrototype, m_nLightID, 0x320)
            CD2_OFFSET(cFlocketPrototype, m_fLightScaleSml, 0x324)
            CD2_OFFSET(cFlocketPrototype, m_fHorizOscil, 0x358))
    };
}

#endif // EQUIP_CFLOCKET_H



