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
#include "fun_runtime/randgen.h"

namespace Equip
{
    class cClusterGrenade : public cExplosiveGrenade
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8261A0F8).
        // Interface only: instance fields and allocation size remain unrecovered.
        // CD2: MakeNew (0x82619728) allocates 0x3B0 and inlines this constructor over cExplosiveGrenadePrototype's
        // (0x821FE7C8); field names and order are RuffKing's (its 0x370..0x37C), CD2's offsets from that constructor
        // and RetRandomBombletSpeed (0x82619920).
        class cClusterGrenadePrototype : public cExplosiveGrenade::cExplosiveGrenadePrototype
        {
        public:
            __forceinline cClusterGrenadePrototype(const RWS::CAttributePacket &packet)
                : cExplosiveGrenade::cExplosiveGrenadePrototype(packet), m_pBombletProto(0), m_nNumBomblets(0),
                  m_fMaxBombletSpeed(0.0f), m_fMinBombletSpeed(0.0f)
            {
            }
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            GOM::cObjectPrototype *m_pBombletProto; // 0x390
            unsigned char m_nNumBomblets;           // 0x394
            float m_fMaxBombletSpeed;               // 0x398
            float m_fMinBombletSpeed;               // 0x39C

        private:
            unsigned char m_unmodelled3A0[0x3B0 - 0x3A0];

            // CD2: cClusterGrenadePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82619F50
        private:
            CD2_LAYOUT_CHECKS(cClusterGrenadePrototype,
                CD2_SIZE(cClusterGrenadePrototype, 0x3B0)
                CD2_OFFSET(cClusterGrenadePrototype, m_pBombletProto, 0x390)
                CD2_OFFSET(cClusterGrenadePrototype, m_nNumBomblets, 0x394)
                CD2_OFFSET(cClusterGrenadePrototype, m_fMaxBombletSpeed, 0x398)
                CD2_OFFSET(cClusterGrenadePrototype, m_fMinBombletSpeed, 0x39C))
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
