// CD2 constructor 0x8260BD28 confirms the shared base constructor chain.
#include "Equip/cCWSatchelCharge.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cMag (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x8260BC88) builds cClass(0x27411, "cMag", 0xB20); 0xB20 is the size its registrar gives.
#ifndef EQUIP_CMAG_H
#define EQUIP_CMAG_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cMag : public Equip::cCWSatchelCharge
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260BC78).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cMagPrototype : public cCWSatchelCharge::cCWSatchelChargePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 factory 0x8260BC60 forwards only this, without a prototype argument.
        cMag();
        // CD2 0x8260BC50: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCCC00 names placement factory 0x8260bc60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMagClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CMAG_H
