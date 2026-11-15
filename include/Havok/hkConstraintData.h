// STAND-IN: Burn's hkConstraintData interface and 0xC-byte layout.
#ifndef HAVOK_HKCONSTRAINTDATA_H
#define HAVOK_HKCONSTRAINTDATA_H
#include "Havok/hkReferencedObject.inl"
#include "Havok/hkBool.h"
class hkConstraintInstance;
struct hkSolverResults;
struct hkConstraintQueryIn;
struct hkConstraintQueryOut;
struct hkConstraintInfo;
class hkConstraintData : public hkReferencedObject
{
public:
    virtual ~hkConstraintData();
    virtual hkBool isValid() const = 0;
    virtual int getType() const = 0;
    struct RuntimeInfo { int m_sizeOfExternalRuntime; int m_numSolverResults; };
    virtual void getRuntimeInfo(hkBool, RuntimeInfo &) const = 0;
    virtual hkSolverResults *getSolverResults(void *);
    virtual void addInstance(hkConstraintInstance *, void *, int) const;
    virtual void buildJacobian(const hkConstraintQueryIn &, hkConstraintQueryOut &) = 0;
    virtual void getConstraintInfo(hkConstraintInfo &) const = 0;
    unsigned int m_userData;
    CD2_LAYOUT_CHECKS(hkConstraintData,
        CD2_SIZE(hkConstraintData, 0xC)
        CD2_OFFSET(hkConstraintData, m_userData, 8))
};
#endif
