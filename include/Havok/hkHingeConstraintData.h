// STAND-IN: Burn's hkHingeConstraintData derives from hkConstraintData, size 0x60.
// CD2 cSpinningProp::CreateConstraintData (0x8273F000) allocates 0x60 bytes.
#ifndef HAVOK_HKHINGECONSTRAINTDATA_H
#define HAVOK_HKHINGECONSTRAINTDATA_H
#include "Havok/hkConstraintData.h"
__declspec(align(16)) class hkHingeConstraintData : public hkConstraintData
{
public:
    virtual ~hkHingeConstraintData();
    virtual hkBool isValid() const;
    virtual int getType() const;
    virtual void getRuntimeInfo(hkBool, RuntimeInfo &) const;
    virtual void buildJacobian(const hkConstraintQueryIn &, hkConstraintQueryOut &);
    virtual void getConstraintInfo(hkConstraintInfo &) const;
private:
    unsigned char m_unmodelledC[0x60 - 0xC];
    CD2_LAYOUT_CHECKS(hkHingeConstraintData, CD2_SIZE(hkHingeConstraintData, 0x60))
};
#endif
