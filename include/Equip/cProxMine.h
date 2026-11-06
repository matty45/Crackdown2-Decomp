// CD2 constructor 0x8261FA00 confirms the shared base constructor chain.
#include "Equip/cCWSatchelCharge.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cProxMine (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8261F960) builds cClass(0x13265, "cProxMine", 0xB10); 0xB10 is the size its registrar gives.
#ifndef EQUIP_CPROXMINE_H
#define EQUIP_CPROXMINE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cProxMine : public Equip::cCWSatchelCharge
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x82621758).
        // CD2's MakeNew (0x8261F8E0) allocates 0x480 and calls the constructor (0x82621370) out of line.
        class cProxMinePrototype : public cCWSatchelCharge::cCWSatchelChargePrototype
        {
        public:
            cProxMinePrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled430[0x480 - 0x430];

            CD2_LAYOUT_CHECKS(cProxMinePrototype,
                CD2_SIZE(cProxMinePrototype, 0x480))
        };

        // CD2 factory 0x8261F948 forwards only this, without a prototype argument.
        cProxMine();
        // CD2 0x8261F870: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8261F880: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x8261FB48.
        virtual ~cProxMine();
        // CD2 0x8261F938: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD0470 names placement factory 0x8261f948.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcProxMineClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPROXMINE_H
