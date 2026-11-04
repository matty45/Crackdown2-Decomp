#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Prop::cExplosiveBarrel (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82743148) is slot 11 of the vtable at 0x8200DA70, as cNonGameBase's RetClassName.
#ifndef PROP_CEXPLOSIVEBARREL_H
#define PROP_CEXPLOSIVEBARREL_H

#include "Prop/cProp.h"

namespace Prop
{
    class cExplosiveBarrel : public Prop::cProp
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 descriptor pointer 0x8384bce0; its initializer names cExplosiveBarrel.
        static const Fun_Runtime::cClass *ms_pccExplosiveBarrelClass;
        // CD2 descriptor 0x8222ee88 names this class; spawning registration 0x82FFA918.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CEXPLOSIVEBARREL_H
