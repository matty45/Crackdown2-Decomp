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
