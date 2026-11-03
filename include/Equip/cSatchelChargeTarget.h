// STAND-IN: RuffKing names/layout; CD2 seven-slot interface +0x7AC has a virtual destructor.
#ifndef CD2_EQUIP_CSATCHELCHARGETARGET_H
#define CD2_EQUIP_CSATCHELCHARGETARGET_H
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"
class cGameBase;
namespace Equip
{
    class cCWSatchelCharge;
    class cSatchelChargeTarget
    {
    private:
        cCWSatchelCharge *m_pFirstSatchel;
    public:
        virtual ~cSatchelChargeTarget();
        virtual bool CanHaveAttachedSatchelCharge(const Fun_Runtime::Vec3 &) const;
        virtual cGameBase *RetSatchelAttachObject();
        virtual Fun_Runtime::Mtx RetSCTransform(int);
        virtual int RetSCBone(Fun_Runtime::Vec3);
    protected:
        virtual void OnAttachSatchelCharge(cCWSatchelCharge *);
        virtual void OnDetachSatchelCharge(cCWSatchelCharge *);
        CD2_LAYOUT_CHECKS(cSatchelChargeTarget, CD2_SIZE(cSatchelChargeTarget, 8)
            CD2_OFFSET(cSatchelChargeTarget, m_pFirstSatchel, 4))
    };
}
#endif
