// Havok motion's reference base interface and complete 12-byte storage.
#ifndef HAVOK_HKMOTION_H
#define HAVOK_HKMOTION_H
#include "Havok/hkReferencedObject.h"
class hkStepInfo;
class hkVector4;
struct hkVelocityAccumulator;
class hkMotion : public hkReferencedObject
{
public:
    enum MotionType { MOTION_INVALID, MOTION_DYNAMIC, MOTION_SPHERE_INERTIA,
        MOTION_STABILIZED_SPHERE_INERTIA, MOTION_BOX_INERTIA, MOTION_STABILIZED_BOX_INERTIA,
        MOTION_KEYFRAMED, MOTION_FIXED, MOTION_MAX_ID };
    virtual ~hkMotion();
    virtual MotionType getType() = 0;
    virtual void step(const hkStepInfo &) = 0;
    virtual void applyForcesAndStep(const hkStepInfo &, const hkVector4 &) = 0;
protected:
    virtual hkVelocityAccumulator *applyForcesAndBuildAccumulator(const hkStepInfo &, hkVelocityAccumulator *) = 0;
public:
    virtual const hkVelocityAccumulator *applyAccumulator(const hkStepInfo &, float, const hkVelocityAccumulator *) = 0;
    virtual int getAccumulatorSize() = 0;
    int m_solverData;
    CD2_LAYOUT_CHECKS(hkMotion, CD2_SIZE(hkMotion, 0xC))
};
#endif
