// CD2 simple-controller getters. Reference names and field types agree with Burn/RuffKing.
// Constructor 0x82564780 installs primary table 0x8200A880; later source ranges remain unassigned.
#include "CHARACTER/cCharacterControllerSimple.h"

namespace CHARACTER
{
    void cCharacterControllerSimple::GetPositionPhantom(Fun_Runtime::Vec3 &position) const
    {
        position.Set(m_hkPosition.getQuad().x, m_hkPosition.getQuad().y, m_hkPosition.getQuad().z);
    }

    float cCharacterControllerSimple::RetMaxStandheight()
    {
        return m_CharacterInfo.m_fHeight;
    }

    const hkVector4 & cCharacterControllerSimple::RetStandHalfBox() const
    {
        return m_CharacterInfo.m_LocalAABB;
    }

    hkShapePhantom * cCharacterControllerSimple::RetPtrShapePhantom() const
    {
        return m_pPhantom;
    }

    unsigned int cCharacterControllerSimple::RetCollisionFilterLayer()
    {
        return m_nCollisionFilterLayer;
    }

    bool cCharacterControllerSimple::IsPhantomInWorld() const
    {
        return m_bHasPhysicalPresence;
    }

    bool cCharacterControllerSimple::IsInUnsafePosition() const
    {
        return m_bInUnsafePosition;
    }

    bool cCharacterControllerSimple::IsNearGround() const
    {
        return m_bSupported;
    }

    bool cCharacterControllerSimple::IsStill() const
    {
        return m_bStill;
    }

    bool cCharacterControllerSimple::IsInWater() const
    {
        return m_bInWater;
    }

    void cCharacterControllerSimple::SetIsInWater(bool inWater)
    {
        m_bInWater = inWater;
    }

    eWaterSurfaceState cCharacterControllerSimple::RetWaterSurfaceState() const
    {
        return m_bInWater ? eWSS_On : eWSS_None;
    }

    bool cCharacterControllerSimple::HasSwitchedDirection() const
    {
        return m_bHasSwitchedDirection;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerSimple::RetLinearVelocity() const
    {
        return m_LinearVelocity;
    }

    float cCharacterControllerSimple::Ret2DVelocity() const
    {
        return m_f2DVelocity;
    }

    float cCharacterControllerSimple::Ret2DAverageVelocity() const
    {
        return m_fAverage2DVelocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerSimple::RetLastControlsVelocity()
    {
        return m_LastControlsVelocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerSimple::RetControlsVelocity()
    {
        return m_ControlsVelocity;
    }

    void cCharacterControllerSimple::SetControlsVelocity(const Fun_Runtime::Vec3 &velocity)
    {
        m_ControlsVelocity.Set(velocity.x, 0.0f, velocity.z);
    }

    void cCharacterControllerSimple::ZeroLastControlsVelocity()
    {
        m_LastControlsVelocity.Zero();
        m_vLastAIVelocity.Zero();
    }

    const Fun_Runtime::Vec3 & cCharacterControllerSimple::RetEffectsVelocity()
    {
        return m_EffectVelocity;
    }

    void cCharacterControllerSimple::SetExpensiveCollisionCheck(bool expensive)
    {
        m_bDoExpensiveCollsionCheck = expensive;
    }

    bool cCharacterControllerSimple::GetExpensiveCollisionCheck()
    {
        return m_bDoExpensiveCollsionCheck;
    }

    void cCharacterControllerSimple::SetLastAIVelocity(const Fun_Runtime::Vec3 &velocity)
    {
        m_vLastAIVelocity = velocity;
    }

    void cCharacterControllerSimple::SetLastSpeedModifier(float speedModifier)
    {
        m_fLastSpeedModifier = speedModifier;
    }

    Fun_Runtime::Vec3 cCharacterControllerSimple::GetLastGroundNormal()
    {
        return m_vLastGroundNormal;
    }

    float cCharacterControllerSimple::ApplyVecticalForce(float height, float time)
    {
        float force = RetVecticalForce(height, time);
        SetEffectsYVelocity(force);
        return force;
    }

    float cCharacterControllerSimple::ApplyVecticalForce(float force)
    {
        Fun_Runtime::Vec3 velocity;
        velocity.Set(0.0f, force, 0.0f);
        AddEffectsVelocity(velocity);
        return force;
    }

    void cCharacterControllerSimple::NoUpdate()
    {
        m_bSupported = true;
        m_bInWater = false;
    }

    const hkShape * cCharacterControllerSimple::RetPtrShape() const
    {
        return m_pPhantom->getCollidable()->getShape();
    }

    const hkCollidable * cCharacterControllerSimple::RetPtrCollidable() const
    {
        if (m_pPhantom)
            return m_pPhantom->getCollidable();
        return 0;
    }

    bool cCharacterControllerSimple::HasCollidable() const
    {
        if (!m_pPhantom)
            return false;
        return m_pPhantom->getCollidable() != 0;
    }

    float cCharacterControllerSimple::RetCollisionTollerance() const
    {
        return 0.02f;
    }

    float cCharacterControllerSimple::RetRadius() const
    {
        if (m_bUsingCrouch)
            return m_CharacterInfo.m_fCrouchRadius;
        else if (m_bUsingProne)
            return m_CharacterInfo.m_fHeight;
        return m_CharacterInfo.m_fRadius;
    }

    float cCharacterControllerSimple::RetStandRadius() const
    {
        return m_CharacterInfo.m_fRadius;
    }

    float cCharacterControllerSimple::RetHeight() const
    {
        if (m_bUsingCrouch)
            return m_CharacterInfo.m_fCrouchHeight;
        else if (m_bUsingProne)
            return 0.2f;
        return m_CharacterInfo.m_fHeight;
    }

    float cCharacterControllerSimple::RetHalfHeight() const
    {
        if (m_bUsingCrouch)
            return m_CharacterInfo.m_fCrouchHalfHeight;
        else if (m_bUsingProne)
            return 0.1f;
        return m_CharacterInfo.m_fHalfHeight;
    }

    float cCharacterControllerSimple::RetMinWorldHeight() const
    {
        return m_hkPosition.getQuad().y;
    }

    inline float cCharacterControllerSimple::RetGravity()
    {
        if (m_bUseGravityOverride)
            return m_fGravityOverride;
        return m_CharacterInfo.m_Gravity.getQuad().y;
    }

    float cCharacterControllerSimple::RetVecticalForce(float fHeight, float fTime)
    {
        return (fHeight - RetGravity() * (fTime * fTime) * 0.5f) / fTime;
    }

    void cCharacterControllerSimple::SetGravityOverride(float gravity)
    {
        m_fGravityOverride = gravity;
        m_bUseGravityOverride = true;
    }

    void cCharacterControllerSimple::ResetGravityOverride()
    {
        m_fGravityOverride = 0.0f;
        m_bUseGravityOverride = false;
    }

}
