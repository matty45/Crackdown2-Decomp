// STAND-IN: RuffKing cCWSatchelCharge derives from cExplosiveGrenade.
// CD2 constructor 0x8261A2E0 calls 0x8261D2E0 before initializing its own
// fields. Descriptor 0x8261A248 gives complete size 0xAE0; those fields remain opaque.
#ifndef EQUIP_CCWSATCHELCHARGE_H
#define EQUIP_CCWSATCHELCHARGE_H
#include "Equip/cExplosiveGrenade.h"
namespace Equip
{
    class cCWSatchelCharge : public cExplosiveGrenade
    {
    public:
        // CD2 0x8261A568: restores this class's vtables, then calls the base destructor (out of line: cProxMine's calls it).
        virtual ~cCWSatchelCharge();
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cCWSatchelChargePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype {};

        // CD2 0x8261A210: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCWSatchelChargeClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
    private:
        unsigned char m_unmodelled9D0[0xAE0 - 0x9D0];
        CD2_LAYOUT_CHECKS(cCWSatchelCharge, CD2_SIZE(cCWSatchelCharge, 0xAE0))
    };
}
#endif
