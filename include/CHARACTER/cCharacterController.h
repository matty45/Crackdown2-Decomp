// CHARACTER::cCharacterController's recovered interface prefix and the header's static
// constants, which every object file that includes it copies. Names, namespace and order from the RuffKing PDB
// (shared/character/ccharactercontroller.h, initializers at lines 54-56; fDEG_TO_RAD is in the same objects in Burn).
// CD2 calls cos and tan with the angle as a double (45 and 50 times the float 0.017453, unrounded).
#ifndef CHARACTER_CCHARACTERCONTROLLER_H
#define CHARACTER_CCHARACTERCONTROLLER_H

#include <math.h>
#include "cd2/layout.h"
#include "CHARACTER/eWaterSurfaceState.h"
namespace PHYSICS { class cDynamicBody; class cBody; class cCustomMaterial; struct tShapeCastResult; }
class hkVector4;
class hkShape;
class hkCollidable;
class hkShapePhantom;
struct hkRootCdPoint;
namespace Fun_Runtime { class Vec3; }

namespace CHARACTER
{
    class cCharacter;
    class cCharacterStateData;
    class cCharacterCollisionListener;
    class cCustomPointCollector;
    struct cCharacterInfo;
    // Reference base has no instance data beyond its vptr. This interface prefix covers CD2 slots 0..95;
    // getters and the primary table confirm the recovered ordering. Later slots remain unmodelled.
    // cCharacterControllerComplex's first getters confirm slots 7/8/18/19/23.
    class cCharacterController
    {
    public:
        virtual ~cCharacterController();
        virtual void Setup(const hkVector4 &, const cCharacterInfo &, cCharacter *, unsigned int);
        virtual void UpdateSetup(const cCharacterInfo &, bool);
        virtual void PreUpdate(float);
        virtual void Update(cCharacterStateData *, float);
        virtual void NoUpdate();
        virtual void ProxyUpdate();
        virtual cCharacterCollisionListener *RetPtrListener();
        virtual const Fun_Runtime::Vec3 &RetPlatformVelocity() const;
        virtual void GetPositionPhantom(Fun_Runtime::Vec3 &) const;
        virtual void SetPositionPhantom(const Fun_Runtime::Vec3 &);
        virtual float RetCollisionTollerance() const;
        virtual float RetRadius() const;
        virtual float RetStandRadius() const;
        virtual float RetHeight() const;
        virtual float RetHalfHeight() const;
        virtual float RetMaxWorldHeight() const;
        virtual float RetMinWorldHeight() const;
        virtual float RetMaxStandheight();
        virtual const hkVector4 &RetStandHalfBox() const;
        virtual const hkShape *RetPtrShape() const;
        virtual const hkCollidable *RetPtrCollidable() const;
        virtual bool HasCollidable() const;
        virtual hkShapePhantom *RetPtrShapePhantom() const;
        virtual hkShape *RetPtrMainShape() const;
        virtual unsigned int RetCollisionFilterLayer();
        virtual bool SetCollisionFilter(int, bool);
        virtual void RemovePhysicalPresence(bool);
        virtual void RestorePhysicalPresence(bool, bool);
        virtual bool IsPhantomInWorld() const;
        virtual bool IsInUnsafePosition() const;
        virtual bool IsNearGround() const;
        virtual bool IsNearFlatGround() const;
        virtual bool IsOnGround() const;
        virtual bool IsStill() const;
        virtual bool IsInWater() const;
        virtual void SetIsInWater(bool);
        virtual eWaterSurfaceState RetWaterSurfaceState() const;
        virtual bool IsOnSteps() const;
        virtual bool IsSteppingUp() const;
        virtual bool IsSteppingDown() const;
        virtual bool IsUpperBodyFireFlatBlocked() const;
        virtual bool IsUpperBodyAimBlocked() const;
        virtual bool IsUpperBodyFireBlocked() const;
        virtual bool IsUpperBlodyBlockedBySolidObject() const;
        virtual bool HasSwitchedDirection() const;
        virtual bool IsPartiallySupported() const;
        virtual PHYSICS::cDynamicBody *RetStandingOnBody();
        // CD2 places this predicate before the heading getter; RuffKing lists them in the reverse order.
        virtual bool IsStandingOnBodyAndCanMoveWithBody();
        virtual const hkVector4 &RetStandingOnBodyLocalHeading();
        virtual bool IsPathImpeded() const;
        virtual bool vf51(); // CD2 boolean listener query (0x8255EF00); name/signature unrecovered.
        virtual float ApplyVecticalForce(float);
        virtual float ApplyVecticalForce(float, float);
        virtual float RetVecticalForce(float, float);
        virtual void ForceLinearVelocity(const Fun_Runtime::Vec3 &);
        virtual const Fun_Runtime::Vec3 &RetLinearVelocity() const;
        virtual const Fun_Runtime::Vec3 &RetAverageLinearVelocity() const;
        virtual float Ret2DVelocity() const;
        virtual float Ret2DAverageVelocity() const;
        virtual const Fun_Runtime::Vec3 &RetLastControlsVelocity();
        virtual const Fun_Runtime::Vec3 &RetControlsVelocity();
        virtual void SetControlsVelocity(const Fun_Runtime::Vec3 &);
        virtual void ZeroLastControlsVelocity();
        virtual void SetEffectsVelocity(const Fun_Runtime::Vec3 &);
        virtual void AddEffectsVelocity(const Fun_Runtime::Vec3 &);
        virtual void ZeroEffectsVelocity();
        virtual const Fun_Runtime::Vec3 &RetEffectsVelocity();
        virtual void SetEffectsYVelocity(float);
        virtual float RetEffectsYVelocity();
        virtual void SetADMOffset(const Fun_Runtime::Vec3 &);
        virtual void ZeroAllVelocities();
        virtual void ZeroYVelocity();
        virtual void SetGravityOverride(float);
        virtual void ResetGravityOverride();
        virtual void SetFwdStick(float);
        virtual void SetStrafeStick(float);
        virtual float RetFwdStick() const;
        virtual float RetStrafeStick() const;
        virtual bool IsEnoughRoomToJump(PHYSICS::tShapeCastResult *);
        virtual bool IsEnoughRoomToStand(PHYSICS::tShapeCastResult *);
        virtual bool TryMove(const hkVector4 &, const hkVector4 &, unsigned int, cCustomPointCollector &, cCustomPointCollector *);
        virtual bool TryMove(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &, unsigned int, PHYSICS::tShapeCastResult *, PHYSICS::cBody *, PHYSICS::cCustomMaterial *);
        virtual bool TryMove(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &, float, float, unsigned int, PHYSICS::tShapeCastResult *, PHYSICS::cBody *, PHYSICS::cCustomMaterial *);
        virtual bool TryMove_Fast(const hkVector4 &, const hkVector4 &, PHYSICS::tShapeCastResult *, PHYSICS::cBody *, PHYSICS::cCustomMaterial *);
        virtual bool TryMove_Fast(const hkVector4 &, const hkVector4 &, cCustomPointCollector &, cCustomPointCollector *);
        virtual void ConvertHitToShapeResult(const hkVector4 &, const hkVector4 &, const hkRootCdPoint *, PHYSICS::tShapeCastResult *);
        virtual bool IsSafeCapsulePosition(const hkVector4 &, float, float, unsigned int, PHYSICS::cBody *, const hkCollidable *);
        virtual bool IsSafePosition(const hkVector4 &, PHYSICS::cBody *, const hkCollidable *);
        virtual bool IsSafePosition_Fast(const hkVector4 &, PHYSICS::cBody *, const hkCollidable *);
        virtual void SetExpensiveCollisionCheck(bool);
        virtual bool GetExpensiveCollisionCheck();
        virtual void SetLastAIVelocity(const Fun_Runtime::Vec3 &);
        virtual void SetLastSpeedModifier(float);
        virtual float RetObjectRequiredStrengthLevelTweak(float) const;
        virtual Fun_Runtime::Vec3 GetLastGroundNormal();
        CD2_LAYOUT_CHECKS(cCharacterController, CD2_SIZE(cCharacterController, 4))
    };

    static const float fDEG_TO_RAD = 0.017453f;
    static const float fSlopeDotLimit = (float)cos(45.0 * fDEG_TO_RAD);
    static const float fStepDotLimit = (float)cos(50.0 * fDEG_TO_RAD);
    static const float fStepDotTan = (float)tan(50.0 * fDEG_TO_RAD);
}

#endif // CHARACTER_CCHARACTERCONTROLLER_H
