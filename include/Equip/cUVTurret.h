#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cUVTurret (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8263BC20) builds cClass(0x1326A, "cUVTurret", 0xAB0); 0xAB0 is the size its registrar gives.
#ifndef EQUIP_CUVTURRET_H
#define EQUIP_CUVTURRET_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cUVTurret
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8263BE20).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cUVTurretPrototype : public cCWFirearm::cCWFirearmPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x8263BA68: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8263BB48: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD4B50 names placement factory 0x8263bb58.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcUVTurretClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CUVTURRET_H
