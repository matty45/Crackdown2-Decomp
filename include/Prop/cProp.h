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
#include "Audio/cPhysicsBodyGameObject.h"
#include "Prop/cPropDamageManager.h"
#include "Prop/cPropCollisionManager.h"
#include "AI/cCoverPoint.h"
#include "fun_runtime/safedeletablepointer.h"

namespace Vehicle { class cHelicopter; }

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
            unsigned char m_unmodelled284[0x45A - 0x284];
        public:
            // RuffKing's name and offset; cProp's ShouldHaveObjectPathPhantom (0x8272AA00) tests it.
            bool m_bHasPathPhantom;                         // 0x45A
        private:
            unsigned char m_unmodelled45B[0x47A - 0x45B];
        public:
            // RuffKing's name and offset; DoDynamicPropCoverInvalidation tests it.
            bool m_bCanAffectCover;                         // 0x47A
        private:
            unsigned char m_unmodelled47B[0x4F0 - 0x47B];

        public:
            cPropPrototype(const RWS::CAttributePacket &);   // 0x8272D390
            // Reference override; CD2 prototype slot 5 at 0x8272F190 returns Ret_OK.
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            // CD2 0x8272D688, called by derived prototype attribute handlers.
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cPropPrototype,
                CD2_SIZE(cPropPrototype, 0x4F0)
                CD2_OFFSET(cPropPrototype, m_nMotionType, 0x280)
                CD2_OFFSET(cPropPrototype, m_bHasPathPhantom, 0x45A)
                CD2_OFFSET(cPropPrototype, m_bCanAffectCover, 0x47A))
        };
        // RuffKing's inline (its out-of-line copy 0x822E12E0).
        cPropPrototype *RetPropPrototype() { return static_cast<cPropPrototype *>(m_pPrototype); }
        // Reference name; CD2 broken-state callbacks call 0x8272AFE0 with eMT_DYNAMIC.
        void SetMotion(eMotionType);
    protected:
        // RuffKing's (out of line there); CD2 inlines it into the net-role overrides (0x827296A0).
        void DoDynamicPropCoverInvalidation()
        {
            if (RetPropPrototype()->m_bCanAffectCover)
                AI::cCoverPoint::SetPropCoverValidity(this, false);
        }
    public:

    private:
        unsigned char m_unknown7B4[0x7B8 - 0x7B4];
        // RuffKing's names and types, 0x28..0x70 below RuffKing's offsets; the destructor (0x82729538) destroys them.
        Audio::cPhysicsBodyGameObject m_PropAudio;              // 0x7B8
        cPropDamageManager m_PropDamageManager;                 // 0x880
        cPropCollisionManager m_ColDamageListener;              // 0xA24
        unsigned char m_unknownA2C[0xE20 - 0xA2C];
        Fun_Runtime::cSafeDeletablePointer<Vehicle::cHelicopter> m_pCarrierObj;  // 0xE20

    protected:
        virtual void UpdateRenderMatrix();   // overrides cNonGameBase's slot 26; 0x826DA5B8 (folded with cVehicle's)

        // CD2: cProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x8273B110
        virtual void LeavePhysicalState(); // 27: 0x8272A370
        virtual bool IsAIEntityOwner(Kaim::CEntity *pEntity); // 61: 0x8272C3E8
        virtual bool IsManagedByActivityManager(); // 62: 0x823B8858
        virtual void vf68(); // 68: 0x8272BFA0
        virtual void vf72(); // 72: 0x826D0C18
        virtual void vf103(); // 103: 0x8272CCD8
        virtual void vf104(); // 104: 0x8272D218
        virtual void vf105(); // 105: 0x8272CD70
        virtual void vf106(); // 106: 0x8272D168
        virtual void vf129(); // 129: 0x8272C2F8
        virtual float vf132(); // 132: 0x8272D2B0
        virtual void vf140(); // 140: 0x82729F20
        virtual hkCollidableQualityType RetCollidableQuality(hkMotion::MotionType); // 156: 0x8272F1A0
        virtual void GetLocalAABB(hkAabb *) const; // 174: 0x8272CA50
        virtual void GetWorldAABB(hkAabb *) const; // 175: 0x8272CB28
        virtual void vf176(); // 176: 0x8272CE68
        virtual void GetAIWorldAABB(hkAabb *); // 177: 0x8272CF20
        virtual void vf179(); // 179: 0x82457A68
        virtual void vf226(); // 226: 0x82730450
        // CD2 cProp table 0x8200DFC8 overrides cNetDynamicBody's empty slots.
        virtual void ImpactAudio(float fDeltaVelocity); // 258: 0x82730470
        virtual void ScrapeAudio(float fRelativeVelocity); // 259: 0x82730488
        virtual void PickUpAudio(); // 260: 0x827304A0
        virtual void WaterEntryAudio(float); // 261: 0x82258750
        virtual void WaterExitAudio(float); // 262: 0x827304B8
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
        // CD2 table 0x8200DFC8 owns these entries; cNetDynamicBody retains the body defaults at them.
        virtual void vf86(); // 86: 0x8272B1F0
        virtual void vf87(); // 87: 0x8272B2B0
        virtual void vf91(); // 91: 0x8272B540
        virtual void vf92(); // 92: 0x8272B338
        virtual GOM::cPointOfInterest *RetPointOfInterest(int nPoint); // 122: 0x82457A50
        virtual unsigned char RetNumPointsOfInterest(); // 123: 0x8288FB78
        // CD2 table 0x8200DFC8 overrides these cNetDynamicBody/cDynamicBody slots.
        virtual void vf158(); // 158: 0x8272ADB0
        virtual void TriggerEnterWater(float fWaterLevel); // 284: 0x8272C400
        virtual void TriggerExitWater(float fWaterLevel); // 285: 0x8272C448
        virtual void vf127(); // 127: 0x8272BC10
        virtual void CreateHavokPhysics(); // 153: 0x8272ABE0
        virtual void DeleteHavokPhysics(); // 154: 0x8272AC18
        virtual void CalculateRelevancy(int); // cReplicatedClass 2: 0x827302C0
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x822D76B0
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8272F450
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x8272F878
        virtual void ReplicateHeaderData(); // cReplicatedClass 10: 0x8272F1E0
        virtual unsigned int GetNumObjectIDBits() const; // cReplicatedClass 16: 0x82882258
        // CD2 table 0x8200DFC8 and its secondaries also differ from cNetDynamicBody's (0x82131E80) at these slots
        // (cNetDynamicBody leaves IsSequential and IsOwnedLocally pure).
        virtual void Slot13(); // 13: 0x82729CA8
        virtual void Slot14(); // 14: 0x8272C228
        virtual void TickUpdate(float fDeltaTime); // 23: 0x822C2DF0
        virtual void Slot24(); // 24: 0x8272A7F8
        virtual void vf76(); // 76: 0x8237D638
        virtual void vf217(); // 217: 0x82604F40
        virtual void vf254(); // 254: 0x8272AB30
        virtual cFrame RetStartFrame(GameRenderer::cLODClump &pClump); // 266: 0x821D1C58
        virtual void vf280(); // 280: 0x8272C370
        virtual void vf281(); // 281: 0x8221A208
        virtual void vf282(); // 282: 0x82457A88
        virtual bool ShouldHaveObjectPathPhantom(); // 288: 0x8272AA00
        virtual void vf295(); // 295: 0x82729D80
        virtual void ReleaseAttachedVFX(bool bReleaseNonCullable); // 296: 0x82729DE0
        virtual bool IsA(const Fun_Runtime::cClass &) const; // cRegisteredClass 1: 0x82729318
        virtual bool IsSequential() const; // cReplicatedClass 6: 0x827E56A8
        virtual bool IsOwnedLocally(); // cReplicatedClass 14: 0x82537F88
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const; // cReplicatedClass 22: 0x82889A60
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288D5C0
        virtual cGameBase *RetSatchelAttachObject(); // cSatchelChargeTarget 2: 0x826AB168
        virtual void OnAttachSatchelCharge(Equip::cCWSatchelCharge *); // cSatchelChargeTarget 5: 0x826CE5C8
        virtual void OnDetachSatchelCharge(Equip::cCWSatchelCharge *); // cSatchelChargeTarget 6: 0x8272AB60
    protected:
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *); // cIgnitable 10: 0x8272B5E8
        virtual void EventTriggerEndFire(); // cIgnitable 12: 0x8272B858
    protected:
        CD2_LAYOUT_CHECKS(cProp,
            CD2_SIZE(cProp, 0xE30)
            CD2_OFFSET(cProp, m_PropAudio, 0x7B8)
            CD2_OFFSET(cProp, m_PropDamageManager, 0x880)
            CD2_OFFSET(cProp, m_ColDamageListener, 0xA24)
            CD2_OFFSET(cProp, m_pCarrierObj, 0xE20))

    public:
        // CD2 table 0x8200DFC8 differs from cNetDynamicBody at these inherited slots.
        virtual void EndInterpolationOptional(); // slot 304: 0x82457AB8
        virtual void SetDeletingReason(char); // slot 309: 0x82457AC8
        virtual char GetDeletingReason(); // slot 310: 0x82457AD0
    };
}

#endif // PROP_CPROP_H
