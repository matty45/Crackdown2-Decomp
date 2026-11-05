#include "Equip/cExplosiveGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cClusterGrenade (Crackdown 2): STAND-IN; base cExplosiveGrenade (its inheritance registrar
// 0x82FCF178 names it). CD2's placement factory 0x826197C8 inlines a constructor that adds no fields, and the class has
// no destructor of its own: its deleting-destructor thunks reach cExplosiveGrenade's deleting destructor (identical code folded).
// StaticCreateClass (0x82619888) builds cClass(0x3E8E, "cClusterGrenade", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef EQUIP_CCLUSTERGRENADE_H
#define EQUIP_CCLUSTERGRENADE_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cClusterGrenade : public cExplosiveGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8261A0F8).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cClusterGrenadePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // __forceinline: CD2's placement factory 0x826197C8 inlines this constructor (base call and every vtable store);
        // /Ob1 declines a plain inline constructor with this many stores (docs/matching-notes.md, Inlining).
        __forceinline cClusterGrenade() {}
        // CD2 0x826196B8 and 0x826196C8: registered-class slots 0 and 1 (outside this file's range).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x826197B8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCF230 names placement factory 0x826197c8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcClusterGrenadeClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        CD2_LAYOUT_CHECKS(cClusterGrenade, CD2_SIZE(cClusterGrenade, 0x9D0))
    };
}

#endif // EQUIP_CCLUSTERGRENADE_H
