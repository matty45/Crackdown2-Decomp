// Hierarchy correction: the CD2 interfaces at 0x120, 0x250, 0x294, 0x420,
// 0x510, 0x7A0, 0x7A4 and 0x7AC are now modelled; the historical direct-base
// stand-in described below is superseded.
// Prop::cProp and Prop::cProp::cPropPrototype (Crackdown 2): STAND-INS, sized to CD2. Only what derived props need so
// far. Evidence:
// - cProp is 0xE30 bytes: its registrar (0x82FF5298) registers the class with size 0xE30, and cTrafficLight's first own
//   field (a long long) sits at 0xE30 (cTrafficLight's constructor, 0x82747470).
// - Bases: PHYSICS::cNetDynamicBody (CD2 size 0x7A0, descriptor 0x82687E38), ExplosionManager::cExplosionCallback,
//   AI::cDynamicObstacleOwner and Equip::cSatchelChargeTarget follow the reference order. CD2's constructor
//   0x82337808 confirms their subobjects and the 341-slot primary interface; only cProp's own fields remain opaque.
// - UpdateRenderMatrix is primary vtable slot 26. cProp's vtable (0x8200DFC8) holds 0x826DA5B8 there; that function
//   first calls 0x82683DC0, slot 26 of PHYSICS::cBody's vtable, which copies the body matrix into the frame's render
//   matrix buffer, then updates the objects attached to the body. RuffKing's cProp overrides UpdateRenderMatrix
//   (protected), as does cTrafficLight. 0x826DA5B8 lies in cVehicle's code and the vehicle vtables use it too: cProp's
//   override and cVehicle's are byte-identical and the linker folded them (ICF), so the name here is cProp's.
// - cPropPrototype is 0x4F0 bytes: cProp's MakeNew (0x82729378) allocates 0x4F0 bytes and calls the constructor
//   0x8272D390 with the packet; cTrafficLight's prototype (0x510 bytes) calls the same constructor.
#ifndef PROP_CPROP_H
#define PROP_CPROP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "ExplosionManager/cExplosionCallback.h"
#include "AI/cDynamicObstacleOwner.h"
#include "Equip/cSatchelChargeTarget.h"
#include "gom/object_prototype.h"

namespace Prop
{
    // RuffKing's prop motion types (cProp.h).
    enum eMotionType
    {
        eMT_FIXED = 0,
        eMT_FIXEDUNTILBROKEN,
        eMT_DYNAMIC,
        eMT_MAX,
    };

    class cProp : public PHYSICS::cNetDynamicBody, public ExplosionManager::cExplosionCallback,
        public AI::cDynamicObstacleOwner, public Equip::cSatchelChargeTarget
    {
    public:
        // CD2 0x827293E0: placement factory.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82729410 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2's prop script-host slot holds 0x8245AE28, rather than
        // cDynamicBody's 0x82684BC0 (including the traffic-light table).
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x82729538, called by cTrafficLight's destructor (0x827475C8).
        cProp(GOM::cObjectPrototype *); // CD2 0x82337808
        virtual ~cProp();
        virtual Fun_Runtime::RetVal Term(); // CD2 0x822C5828
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // CD2 0x827296C0, primary slot 18
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        virtual void CreateDynamicObstacle();
        virtual void ActivateDynamicObstacle();
        virtual unsigned char GetDynamicObstacleInput();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2's cProp table 0x8200DFC8 has 341 primary slots, extending cNetDynamicBody's 314.
        // These slot indices are retained until the individual virtual names/signatures are recovered.
        virtual void Breakoff(bool bForce); virtual void vf315(); virtual void vf316(); virtual void OnSpawnedAsFragment(cGameBase *pParent); virtual void vf318();
        virtual void vf319(); virtual void vf320(); virtual void vf321(); virtual void vf322(); virtual void vf323();
        virtual void vf324(); virtual void vf325(); virtual void vf326(); virtual void vf327(); virtual void vf328();
        virtual void vf329(); virtual void vf330(); virtual void vf331(); virtual void vf332(); virtual void vf333();
        virtual void vf334(); virtual unsigned int RetInteractionAnimID() const; virtual void vf336(); virtual void vf337(); virtual void vf338();
        virtual void vf339(); virtual void vf340();
        class cPropPrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype
        {
        public:
            // RuffKing's first own field; CD2's cSpinningProp::GoToInitialState (0x8273EC48) compares it with eMT_DYNAMIC.
            eMotionType m_nMotionType;                      // 0x280
        private:
            unsigned char m_unmodelled284[0x4F0 - 0x284];

        public:
            cPropPrototype(const RWS::CAttributePacket &);   // 0x8272D390
            // CD2 0x8272D688, called by derived prototype attribute handlers.
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cPropPrototype,
                CD2_SIZE(cPropPrototype, 0x4F0)
                CD2_OFFSET(cPropPrototype, m_nMotionType, 0x280))
        };

    private:
        unsigned char m_unknown7B4[0xE30 - 0x7B4];

    protected:
        virtual void UpdateRenderMatrix();   // overrides cNonGameBase's slot 26; 0x826DA5B8 (folded with cVehicle's)

        // CD2: cProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x8273B110
        virtual void Slot27(); // 27: 0x8272A370
        virtual void Slot62(); // 61: 0x8272C3E8
        virtual void Slot63(); // 62: 0x823B8858
        virtual void vf68(); // 68: 0x8272BFA0
        virtual void vf72(); // 72: 0x826D0C18
        virtual void vf103(); // 103: 0x8272CCD8
        virtual void vf104(); // 104: 0x8272D218
        virtual void vf105(); // 105: 0x8272CD70
        virtual void vf106(); // 106: 0x8272D168
        virtual void vf129(); // 129: 0x8272C2F8
        virtual void vf132(); // 132: 0x8272D2B0
        virtual void vf140(); // 140: 0x82729F20
        virtual void vf156(); // 156: 0x8272F1A0
        virtual void vf174(); // 174: 0x8272CA50
        virtual void vf175(); // 175: 0x8272CB28
        virtual void vf176(); // 176: 0x8272CE68
        virtual void vf177(); // 177: 0x8272CF20
        virtual void vf179(); // 179: 0x82457A68
        virtual void vf226(); // 226: 0x82730450
        // CD2 cProp table 0x8200DFC8 overrides cNetDynamicBody's empty slots.
        virtual void vf258(); // 258: 0x82730470
        virtual void vf259(); // 259: 0x82730488
        virtual void vf260(); // 260: 0x827304A0
        virtual void vf261(); // 261: 0x82258750
        virtual void vf262(); // 262: 0x827304B8
        virtual void EnterGhostState(); // 271: 0x8272AAC8
        virtual void vf283(); // 283: 0x823A22E0
        virtual void OnEnterNetRoleAuthority(etNetRole); // cNetRoleObject 2: 0x827296A0
        virtual void OnEnterNetRoleSimulated(etNetRole); // cNetRoleObject 3: 0x827296A0
        virtual void SetPingedFieldStatesForNode(unsigned char); // cReplicatedClass 20: 0x827303C0
        virtual char const * RetName() const; // cSafeDeletable 4: 0x8272C3E0
    protected:
        // CD2: cProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot64(); // 63: 0x82689C78
        virtual void vf92(); // 92: 0x8272B338
        virtual void vf127(); // 127: 0x8272BC10
        virtual void CalculateRelevancy(int); // cReplicatedClass 2: 0x827302C0
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x822D76B0
        virtual void ReplicateHeaderData(); // cReplicatedClass 10: 0x8272F1E0
    protected:
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *); // cIgnitable 10: 0x8272B5E8
        virtual void EventTriggerEndFire(); // cIgnitable 12: 0x8272B858
    protected:
        CD2_LAYOUT_CHECKS(cProp,
            CD2_SIZE(cProp, 0xE30))

    public:
        // CD2 table 0x8200DFC8 differs from cNetDynamicBody at these inherited slots.
        virtual void vf304(); // slot 304: 0x82457AB8
        virtual void vf309(); // slot 309: 0x82457AC8
        virtual void vf310(); // slot 310: 0x82457AD0
    };
}

#endif // PROP_CPROP_H
