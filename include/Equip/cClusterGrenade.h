#include "Equip/cExplosiveGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cClusterGrenade (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82619888) builds cClass(0x3E8E, "cClusterGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CCLUSTERGRENADE_H
#define EQUIP_CCLUSTERGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cClusterGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8261A0F8).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cClusterGrenadePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x826197B8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCF230 names placement factory 0x826197c8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcClusterGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCLUSTERGRENADE_H
