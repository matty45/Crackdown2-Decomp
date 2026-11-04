#include "Equip/cGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cSmokeGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82622790) builds cClass(0x3E8D, "cSmokeGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CSMOKEGRENADE_H
#define EQUIP_CSMOKEGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cSmokeGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x82622D80).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cSmokeGrenadePrototype : public cGrenade::cGrenadePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x826225D0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826226C0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD0C70 names placement factory 0x826226d0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSmokeGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CSMOKEGRENADE_H
