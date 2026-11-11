#include "Equip/cExplosiveGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cShrapnelGrenade (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cExplosiveGrenade: the destructor 0x82621D08 calls cExplosiveGrenade's (0x8261D3F0).
// StaticCreateClass (0x82621C20) builds cClass(0x3E8C, "cShrapnelGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CSHRAPNELGRENADE_H
#define EQUIP_CSHRAPNELGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cShrapnelGrenade : public cExplosiveGrenade
    {
    public:
        // __forceinline: CD2's placement factory 0x82621B60 inlines this constructor (base call and every vtable
        // store); /Ob1 declines a plain inline constructor with this many stores (docs/matching-notes.md, Inlining).
        __forceinline cShrapnelGrenade() {}
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x82622568).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cShrapnelGrenadePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 0x82621A60: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82621A70: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x82621D08.
        virtual ~cShrapnelGrenade();
        // CD2 0x82621B50: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD0998 names placement factory 0x82621b60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcShrapnelGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    public:
        // CD2 table 0x82124760 differs from cExplosiveGrenade at these inherited slots.
        virtual void vf419(); // slot 419: 0x82621DA8
    };
}

#endif // EQUIP_CSHRAPNELGRENADE_H
