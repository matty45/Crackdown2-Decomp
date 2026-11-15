// STAND-IN: Burn/RuffKing hkMotorAction hierarchy and named fields.
// CD2 cSpinningProp's motor cleanup (0x8273F538) uses the inherited world/ref-count fields.
#ifndef HAVOK_HKMOTORACTION_H
#define HAVOK_HKMOTORACTION_H
#include "Havok/hkUnaryAction.h"
#include "Havok/hkReferencedObject.inl"
#include "Havok/hkVector4.h"
#include "Havok/hkBool.h"
class hkMotorAction : public hkUnaryAction
{
public:
    virtual ~hkMotorAction();
    virtual void applyAction(const hkStepInfo &);
    virtual hkAction *clone(const hkArray<hkEntity *> &, const hkArray<hkPhantom *> &);
protected:
    hkVector4 m_axis;
    float m_spinRate;
    float m_gain;
    hkBool m_active;
    CD2_LAYOUT_CHECKS(hkMotorAction,
        CD2_SIZE(hkMotorAction, 0x40)
        CD2_OFFSET(hkMotorAction, m_axis, 0x20)
        CD2_OFFSET(hkMotorAction, m_spinRate, 0x30)
        CD2_OFFSET(hkMotorAction, m_gain, 0x34)
        CD2_OFFSET(hkMotorAction, m_active, 0x38))
};
#endif
