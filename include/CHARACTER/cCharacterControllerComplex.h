// STAND-IN: reference complex-controller base and named member prefix. CD2 constructor 0x82282670
// installs primary table 0x821147D8. Getter bodies confirm the checked offsets below.
// The complete allocation size, later storage and remaining virtual interface are not asserted or instantiated.
#ifndef CHARACTER_CCHARACTERCONTROLLERCOMPLEX_H
#define CHARACTER_CCHARACTERCONTROLLERCOMPLEX_H
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cCharacterInfo.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/safedeletablepointer.h"
#include "PHYSICS/cDynamicBody.h"
class hkAabbPhantom;
class hkListShape;
namespace CHARACTER
{
    class cCustomCharacterProxy;
    class cCharacterControllerComplex : public cCharacterController
    {
    public:
        virtual ~cCharacterControllerComplex();
        virtual void GetPositionPhantom(Fun_Runtime::Vec3 &) const;
        virtual void SetControlsVelocity(const Fun_Runtime::Vec3 &);
        virtual void ZeroLastControlsVelocity();
        virtual void SetEffectsVelocity(const Fun_Runtime::Vec3 &);
        virtual void SetADMOffset(const Fun_Runtime::Vec3 &);
        virtual cCharacterCollisionListener *RetPtrListener();
        virtual const Fun_Runtime::Vec3 &RetPlatformVelocity() const;
        virtual float RetMaxStandheight();
        virtual const hkVector4 &RetStandHalfBox() const;
        virtual hkShapePhantom *RetPtrShapePhantom() const;
        virtual bool IsPhantomInWorld() const;
        virtual bool IsInUnsafePosition() const;
        virtual bool IsNearGround() const;
        virtual bool IsNearFlatGround() const;
        virtual bool IsOnGround() const;
        virtual bool IsStill() const;
        virtual bool IsInWater() const;
        virtual void SetIsInWater(bool inWater);
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
        virtual PHYSICS::cDynamicBody * RetStandingOnBody();
        virtual const hkVector4 & RetStandingOnBodyLocalHeading();
        virtual const Fun_Runtime::Vec3 & RetLinearVelocity() const;
        virtual const Fun_Runtime::Vec3 & RetAverageLinearVelocity() const;
        virtual float Ret2DVelocity() const;
        virtual float Ret2DAverageVelocity() const;
        virtual const Fun_Runtime::Vec3 & RetLastControlsVelocity();
        virtual const Fun_Runtime::Vec3 & RetControlsVelocity();
        virtual const Fun_Runtime::Vec3 & RetEffectsVelocity();
        virtual void SetEffectsYVelocity(float velocity);
        virtual float RetEffectsYVelocity();
        virtual void SetFwdStick(float value);
        virtual void SetStrafeStick(float value);
        virtual float RetFwdStick() const;
        virtual float RetStrafeStick() const;
    private:
        // Own cast-result and averaging storage before the dimensions is unrecovered.
        unsigned char m_unmodelled4[0xE0 - 4];
        cCharacterInfo m_CharacterInfo;
        cCharacter *m_pCharacter;
        unsigned int m_nCollisionFilterLayer;
        float m_fDistSqMoved;
        float m_fTimeStill;
        float m_fLastGroundAccel;
        float m_fLastGroundDecel;
        float m_fLastGroundVelStore;
        Fun_Runtime::Vec3 m_DepenetrationVelocity;
        Fun_Runtime::Vec3 m_EffectVelocity;
        Fun_Runtime::Vec3 m_ControlsVelocity;
        Fun_Runtime::Vec3 m_LastControlsVelocity;
        Fun_Runtime::Vec3 m_LinearVelocity;
        Fun_Runtime::Vec3 m_PlatformVelcoity;
        float m_f2DVelocity;
        float m_f2DVelocityStore;
        Fun_Runtime::Vec3 m_vADMOffset;
        Fun_Runtime::Vec3 m_vInitWingLinearVel;
        float m_fWingInitDot;
        float m_fPrevWing2DVel;
        float m_fPrevWingStrafeVel;
        float m_fPrevWingBankVel;
        float m_fFBWingAngAccel;
        float m_fFBWingAngSpeed;
        float m_fStrafeWingAngAccel;
        float m_fStrafeWingAngSpeed;
        float m_fBankWingAngSpeed;
        float m_fFBWingAng;
        float m_fStrafeWingAng;
        float m_fBankWingAng;
        float m_fWingSuitUpdraft;
        float m_fWingSuitPullBackAccum;
        bool m_bWingSuitTriggerPullBack;
        float m_fAverage2DVelocity;
        Fun_Runtime::Vec3 m_AverageLinearVelocity;
        cCustomCharacterProxy *m_pCharacterProxy;
        hkShapePhantom *m_pPhantom;
        hkAabbPhantom *m_pAABBPhantom;
        hkShape *m_pCarriedShape;
        cCharacterCollisionListener *m_pListener;
        hkListShape *m_pListShape;
        Fun_Runtime::Vec3 m_vNearGroundNormal;
        Fun_Runtime::Vec3 m_vNearGroundAverageNormal;
        Fun_Runtime::Vec3 m_vSepNormal;
        float m_fSepDistance;
        float m_fWaterTimer;
        eWaterSurfaceState m_eWaterSurfaceState;
        hkVector4 m_hkPosition;
        hkVector4 m_hkLinearVelocity;
        float m_fStickFwd;
        float m_fStickStrafe;
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pStandingOnBody;
        hkVector4 m_StandingPoint;
        hkVector4 m_StandingPointInBodySpace;
        hkVector4 m_StandingOnBodyLocalHeading;
        // CD2 getter masks require this declaration order within each byte; field names follow the references.
        // The three bytes at +0x300..+0x302 have the opposite bit declaration order to the later reference.
        unsigned char m_bHasAnimDrivenMovement : 1;
        unsigned char m_bStill : 1;
        unsigned char m_bHasObjectInPhysicalPresence : 1;
        unsigned char m_bHasPhysicalPresence : 1;
        unsigned char m_bInWater : 1;
        unsigned char m_bOnWaterSuface : 1;
        unsigned char m_bInUnsafePosition : 1;
        unsigned char m_bIsUpperBodyFlatBlocked : 1;
        unsigned char m_bIsUpperBodyAimBlocked : 1;
        unsigned char m_bIsUpperBodyFireBlocked : 1;
        unsigned char m_bIsUpperBlodyBlockedBySolidObject : 1;
        unsigned char m_bIsOnSteps : 1;
        unsigned char m_bIsSteppingUp : 1;
        unsigned char m_bIsSteppingDown : 1;
        unsigned char m_bPartiallySupported : 1;
        unsigned char m_bSupported : 1;
        unsigned char m_bNearGround : 1;
        unsigned char m_bNearFlatGround : 1;
        unsigned char m_bUseCylinderShape : 1;
        unsigned char m_bUsingCrouch : 1;
        unsigned char m_bUsingProne : 1;
        unsigned char m_bHasSwitchedDirection : 1;
        unsigned char m_bWarpped : 1;
        unsigned char m_bNoGravity : 1;
        CD2_LAYOUT_CHECKS(cCharacterControllerComplex,
            CD2_OFFSET(cCharacterControllerComplex, m_CharacterInfo, 0xE0)
            CD2_OFFSET(cCharacterControllerComplex, m_PlatformVelcoity, 0x1A0)
            CD2_OFFSET(cCharacterControllerComplex, m_pPhantom, 0x234)
            CD2_OFFSET(cCharacterControllerComplex, m_pListener, 0x240)
            CD2_OFFSET(cCharacterControllerComplex, m_StandingOnBodyLocalHeading, 0x2F0)
            CD2_OFFSET(cCharacterControllerComplex, m_fStickFwd, 0x2B0))
    };
}
#endif
