// CD2 constructor 0x8260DF18 confirms the shared base constructor chain.
#include "Equip/cCWSatchelCharge.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cPortableLaunchPad (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8260DE78) builds cClass(0x27412, "cPortableLaunchPad", 0xCA0); 0xCA0 is the size its registrar gives.
#ifndef EQUIP_CPORTABLELAUNCHPAD_H
#define EQUIP_CPORTABLELAUNCHPAD_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cPortableLaunchPad : public Equip::cCWSatchelCharge
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260DE68).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cJumpPadPrototype : public cCWSatchelCharge::cCWSatchelChargePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 factory 0x8260DE50 forwards only this, without a prototype argument.
        cPortableLaunchPad();
        // CD2 0x8260DE40: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCCEA0 names placement factory 0x8260de50.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPortableLaunchPadClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPORTABLELAUNCHPAD_H
