// CD2's complex-controller getter range; names and field types agree with Burn/RuffKing.
// Table 0x821147D8 is installed by constructor 0x82282670; later source ranges remain unassigned.
#include "CHARACTER/cCharacterControllerComplex.h"

namespace CHARACTER
{
    cCharacterCollisionListener *cCharacterControllerComplex::RetPtrListener()
    {
        return m_pListener;
    }

    const Fun_Runtime::Vec3 &cCharacterControllerComplex::RetPlatformVelocity() const
    {
        return m_PlatformVelcoity;
    }

    void cCharacterControllerComplex::GetPositionPhantom(Fun_Runtime::Vec3 &position) const
    {
        position.Set(m_hkPosition.getQuad().x, m_hkPosition.getQuad().y, m_hkPosition.getQuad().z);
    }

    float cCharacterControllerComplex::RetMaxStandheight()
    {
        return m_CharacterInfo.m_fHeight;
    }

    const hkVector4 &cCharacterControllerComplex::RetStandHalfBox() const
    {
        return m_CharacterInfo.m_LocalAABB;
    }

    hkShapePhantom *cCharacterControllerComplex::RetPtrShapePhantom() const
    {
        return m_pPhantom;
    }
    bool cCharacterControllerComplex::IsPhantomInWorld() const
    {
        return m_bHasPhysicalPresence;
    }

    bool cCharacterControllerComplex::IsInUnsafePosition() const
    {
        return m_bInUnsafePosition;
    }

    bool cCharacterControllerComplex::IsNearGround() const
    {
        return m_bNearGround;
    }

    bool cCharacterControllerComplex::IsNearFlatGround() const
    {
        return m_bNearFlatGround;
    }

    bool cCharacterControllerComplex::IsOnGround() const
    {
        return m_bSupported;
    }

    bool cCharacterControllerComplex::IsStill() const
    {
        return m_bStill;
    }

    bool cCharacterControllerComplex::IsInWater() const
    {
        return m_bInWater;
    }

    void cCharacterControllerComplex::SetIsInWater(bool inWater)
    {
        m_bInWater = inWater;
    }

    eWaterSurfaceState cCharacterControllerComplex::RetWaterSurfaceState() const
    {
        return m_eWaterSurfaceState;
    }

    bool cCharacterControllerComplex::IsOnSteps() const
    {
        return m_bIsOnSteps;
    }

    bool cCharacterControllerComplex::IsSteppingUp() const
    {
        return m_bIsSteppingUp;
    }

    bool cCharacterControllerComplex::IsSteppingDown() const
    {
        return m_bIsSteppingDown;
    }

    bool cCharacterControllerComplex::IsUpperBodyFireFlatBlocked() const
    {
        return m_bIsUpperBodyFlatBlocked;
    }

    bool cCharacterControllerComplex::IsUpperBodyAimBlocked() const
    {
        return m_bIsUpperBodyAimBlocked;
    }

    bool cCharacterControllerComplex::IsUpperBodyFireBlocked() const
    {
        return m_bIsUpperBodyFireBlocked;
    }

    bool cCharacterControllerComplex::IsUpperBlodyBlockedBySolidObject() const
    {
        return m_bIsUpperBlodyBlockedBySolidObject;
    }

    bool cCharacterControllerComplex::HasSwitchedDirection() const
    {
        return m_bHasSwitchedDirection;
    }

    bool cCharacterControllerComplex::IsPartiallySupported() const
    {
        return m_bPartiallySupported;
    }

    PHYSICS::cDynamicBody * cCharacterControllerComplex::RetStandingOnBody()
    {
        return m_pStandingOnBody;
    }

    const hkVector4 & cCharacterControllerComplex::RetStandingOnBodyLocalHeading()
    {
        return m_StandingOnBodyLocalHeading;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerComplex::RetLinearVelocity() const
    {
        return m_LinearVelocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerComplex::RetAverageLinearVelocity() const
    {
        return m_AverageLinearVelocity;
    }

    float cCharacterControllerComplex::Ret2DVelocity() const
    {
        return m_f2DVelocity;
    }

    float cCharacterControllerComplex::Ret2DAverageVelocity() const
    {
        return m_fAverage2DVelocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerComplex::RetLastControlsVelocity()
    {
        return m_LastControlsVelocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerComplex::RetControlsVelocity()
    {
        return m_ControlsVelocity;
    }

    void cCharacterControllerComplex::SetControlsVelocity(const Fun_Runtime::Vec3 &velocity)
    {
        // Control input is horizontal; the supplied vertical component is discarded.
        m_ControlsVelocity.Set(velocity.x, 0.0f, velocity.z);
    }

    void cCharacterControllerComplex::ZeroLastControlsVelocity()
    {
        m_LastControlsVelocity.Zero();
    }

    void cCharacterControllerComplex::SetEffectsVelocity(const Fun_Runtime::Vec3 &velocity)
    {
        m_EffectVelocity = velocity;
    }

    const Fun_Runtime::Vec3 & cCharacterControllerComplex::RetEffectsVelocity()
    {
        return m_EffectVelocity;
    }

    void cCharacterControllerComplex::SetEffectsYVelocity(float velocity)
    {
        m_EffectVelocity.y = velocity;
    }

    float cCharacterControllerComplex::RetEffectsYVelocity()
    {
        return m_EffectVelocity.y;
    }

    void cCharacterControllerComplex::SetADMOffset(const Fun_Runtime::Vec3 &offset)
    {
        m_vADMOffset = offset;
    }

    void cCharacterControllerComplex::SetFwdStick(float value)
    {
        m_fStickFwd = value;
    }

    void cCharacterControllerComplex::SetStrafeStick(float value)
    {
        m_fStickStrafe = value;
    }

    float cCharacterControllerComplex::RetFwdStick() const
    {
        return m_fStickFwd;
    }

    float cCharacterControllerComplex::RetStrafeStick() const
    {
        return m_fStickStrafe;
    }

}
