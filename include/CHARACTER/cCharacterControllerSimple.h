// STAND-IN: reference simple-controller member prefix over the complete four-byte base.
// CD2 constructor 0x82564780 installs table 0x8200A880 at 0x825647C0. Its getters confirm
// the dimensions, velocities, phantom, position and flag offsets below. Not instantiated.
#ifndef CHARACTER_CCHARACTERCONTROLLERSIMPLE_H
#define CHARACTER_CCHARACTERCONTROLLERSIMPLE_H
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cCharacterInfo.h"
#include "fun_runtime/vec3.h"
class hkListShape;
class hkAabbPhantom;
namespace CHARACTER
{
    class cCharacterControllerSimple : public cCharacterController
    {
    public:
        virtual ~cCharacterControllerSimple();
        virtual void SetGravityOverride(float);
        virtual void ResetGravityOverride();
        virtual void GetPositionPhantom(Fun_Runtime::Vec3 &position) const;
        virtual float RetMaxStandheight();
        virtual const hkVector4 & RetStandHalfBox() const;
        virtual hkShapePhantom * RetPtrShapePhantom() const;
        virtual unsigned int RetCollisionFilterLayer();
        virtual bool IsPhantomInWorld() const;
        virtual bool IsInUnsafePosition() const;
        virtual bool IsNearGround() const;
        virtual bool IsStill() const;
        virtual bool IsInWater() const;
        virtual void SetIsInWater(bool inWater);
        virtual bool HasSwitchedDirection() const;
        virtual const Fun_Runtime::Vec3 & RetLinearVelocity() const;
        virtual float Ret2DVelocity() const;
        virtual float Ret2DAverageVelocity() const;
        virtual const Fun_Runtime::Vec3 & RetLastControlsVelocity();
        virtual const Fun_Runtime::Vec3 & RetControlsVelocity();
        virtual void SetControlsVelocity(const Fun_Runtime::Vec3 &velocity);
        virtual void ZeroLastControlsVelocity();
        virtual const Fun_Runtime::Vec3 & RetEffectsVelocity();
        virtual void SetExpensiveCollisionCheck(bool expensive);
        virtual bool GetExpensiveCollisionCheck();
        virtual void SetLastAIVelocity(const Fun_Runtime::Vec3 &velocity);
        virtual void SetLastSpeedModifier(float speedModifier);
        virtual Fun_Runtime::Vec3 GetLastGroundNormal();
    private:
        // Own averaging storage at +0x10 is not yet modelled.
        unsigned char m_unmodelledAveraging[0x70 - 4];
        cCharacterInfo m_CharacterInfo;
        cCharacter *m_pCharacter;
        unsigned int m_nCollisionFilterLayer;
        Fun_Runtime::Vec3 m_EffectVelocity;
        Fun_Runtime::Vec3 m_ControlsVelocity;
        Fun_Runtime::Vec3 m_LastControlsVelocity;
        Fun_Runtime::Vec3 m_LinearVelocity;
        float m_f2DVelocity;
        float m_fAverage2DVelocity;
        float m_fGravityOverride;
        Fun_Runtime::Vec3 m_vLastAIVelocity;
        float m_fLastSpeedModifier;
        hkShapePhantom *m_pPhantom;
        hkListShape *m_pListShape;
        hkAabbPhantom *m_pAABBPhantom;
        hkShapePhantom *m_pDetailPhantom;
        float m_fUnsupportedTimer;
        // Own ray-triangle caches and their alignment before the position remain unrecovered.
        unsigned char m_unmodelledRayCaches[0x230 - 0x148];
        hkVector4 m_hkPosition;
        // CD2 converts this three-component value to Vec3, supplying w=1 on return.
        Fun_Runtime::OldVec3 m_vLastGroundNormal;
        // CD2 masks, rather than the later reference declaration order, establish these bit positions.
        unsigned char m_bStill : 1;
        unsigned char m_unrecoveredFlags65 : 2;
        unsigned char m_bDoExpensiveCollsionCheck : 1;
        unsigned char m_unrecoveredFlag3 : 1;
        unsigned char m_bHasPhysicalPresence : 1;
        unsigned char m_bInWater : 1;
        unsigned char m_bInUnsafePosition : 1;
        unsigned char m_bSupported : 1;
        unsigned char m_unrecoveredFlags654 : 3;
        unsigned char m_bHasSwitchedDirection : 1;
        unsigned char m_bUseGravityOverride : 1;
        unsigned char m_unrecoveredFlags10 : 2;
        CD2_LAYOUT_CHECKS(cCharacterControllerSimple,
            CD2_OFFSET(cCharacterControllerSimple, m_CharacterInfo, 0x70)
            CD2_OFFSET(cCharacterControllerSimple, m_LinearVelocity, 0x100)
            CD2_OFFSET(cCharacterControllerSimple, m_vLastAIVelocity, 0x120)
            CD2_OFFSET(cCharacterControllerSimple, m_pPhantom, 0x134)
            CD2_OFFSET(cCharacterControllerSimple, m_hkPosition, 0x230)
            CD2_OFFSET(cCharacterControllerSimple, m_vLastGroundNormal, 0x240))
    };
}
#endif
