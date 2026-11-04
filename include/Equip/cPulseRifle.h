#include "Equip/cCWWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cPulseRifle (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8260FAA0) builds cClass(0x27413, "cPulseRifle", 0xA80); 0xA80 is the size its registrar gives.
#ifndef EQUIP_CPULSERIFLE_H
#define EQUIP_CPULSERIFLE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cPulseRifle
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260EE18).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cPulseRiflePrototype : public cCWWeapon::cCWWeaponPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x8260ED38: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCD2D8 names placement factory 0x8260ed48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPulseRifleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CPULSERIFLE_H
