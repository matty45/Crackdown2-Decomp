#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Prop::cExplosiveBarrel (Crackdown 2): STAND-IN; m_nDeleteTime from RuffKing (0xEA0 there). Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82743148) is slot 11 of the vtable at 0x8200DA70, as cNonGameBase's RetClassName.
#ifndef PROP_CEXPLOSIVEBARREL_H
#define PROP_CEXPLOSIVEBARREL_H

#include "Prop/cProp.h"

namespace Prop
{
    class cExplosiveBarrel : public Prop::cProp
    {
    public:
        // CD2's placement factory 0x82743158 inlines this constructor: cProp's constructor (0x82337808), the vtables, then
        // m_nDeleteTime. __forceinline: /Ob1 declines a plain inline constructor with this many stores (docs/matching-notes.md).
        __forceinline cExplosiveBarrel(GOM::cObjectPrototype *pPrototype) : cProp(pPrototype), m_nDeleteTime(0) {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82743068: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 descriptor pointer 0x8384bce0; its initializer names cExplosiveBarrel.
        static const Fun_Runtime::cClass *ms_pccExplosiveBarrelClass;
        // CD2 descriptor 0x8222ee88 names this class; spawning registration 0x82FFA918.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        unsigned int m_nDeleteTime;

        CD2_LAYOUT_CHECKS(cExplosiveBarrel,
            CD2_SIZE(cExplosiveBarrel, 0xE40)
            CD2_OFFSET(cExplosiveBarrel, m_nDeleteTime, 0xE30))
    };
}

#endif // PROP_CEXPLOSIVEBARREL_H
