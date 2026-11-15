// STAND-IN: Burn's hkPrismaticConstraintData interface, base and 0xA0-byte size.
// CD2 cPrismaticProp::DestroyConstraintData (0x8273C570) inlines reference release.
#ifndef HAVOK_HKPRISMATICCONSTRAINTDATA_H
#define HAVOK_HKPRISMATICCONSTRAINTDATA_H
#include "Havok/hkConstraintData.h"
class hkConstraintMotor;
__declspec(align(16)) class hkPrismaticConstraintData : public hkConstraintData
{
public:
    virtual ~hkPrismaticConstraintData();
    virtual hkBool isValid() const;
    virtual int getType() const;
    virtual void getRuntimeInfo(hkBool, RuntimeInfo &) const;
    virtual void buildJacobian(const hkConstraintQueryIn &, hkConstraintQueryOut &);
    virtual void getConstraintInfo(hkConstraintInfo &) const;
    void setMotor(hkConstraintMotor *);
private:
    unsigned char m_unmodelledC[0xA0 - 0xC];
    CD2_LAYOUT_CHECKS(hkPrismaticConstraintData, CD2_SIZE(hkPrismaticConstraintData, 0xA0))
};
#endif
