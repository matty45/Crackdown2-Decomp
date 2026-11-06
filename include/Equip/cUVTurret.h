#include "Equip/cCWFirearm.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cUVTurret (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWFirearm: CD2's inheritance registrar names it, and the destructor 0x8263BD10 calls cCWFirearm's (0x82617EB8).
// StaticCreateClass (0x8263BC20) builds cClass(0x1326A, "cUVTurret", 0xAB0); 0xAB0 is the size its registrar gives.
#ifndef EQUIP_CUVTURRET_H
#define EQUIP_CUVTURRET_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cUVTurret : public cCWFirearm
    {
    public:
        // Inline: CD2's placement factory (0x8263BB58) calls cCWFirearm's (0x821F0768) constructor, then stores this class's vptrs.
        __forceinline cUVTurret() {}
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8263BE20).
        // CD2's MakeNew (0x8263BAD8) allocates 0x6E0 and inlines the constructor: no fields of its own.
        class cUVTurretPrototype : public cCWFirearm::cCWFirearmPrototype
        {
        public:
            __forceinline cUVTurretPrototype(const RWS::CAttributePacket &packet)
                : cCWFirearm::cCWFirearmPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cUVTurretPrototype,
                CD2_SIZE(cUVTurretPrototype, 0x6E0))
        };

        // CD2 0x8263BA68: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x8263BA78: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x8263BD10.
        virtual ~cUVTurret();
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
