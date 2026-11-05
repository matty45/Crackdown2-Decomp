// Prop::cPrismaticProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273B5A0) is slot 11 of the vtable at 0x821405E8, as cNonGameBase's RetClassName.
#ifndef PROP_CPRISMATICPROP_H
#define PROP_CPRISMATICPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cPrismaticProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 placement factory 0x8273B5B0; constructor signature follows RuffKing.
        cPrismaticProp(GOM::cObjectPrototype *);
        // CD2 0x8273BC98: restores this class's vtables (primary 0x821405E8), then calls the base destructor.
        // Out of line: cLift's and cWeaponCabinetDoor's destructors call it.
        virtual ~cPrismaticProp();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing layout; CD2 factory 0x8273B548 allocates 0x530 and calls constructor 0x8273CBD0.
        class cPrismaticPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cPrismaticPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fMinLinearLimit;
            float m_fMaxLinearLimit;
            float m_fSlideSpeed;
            float m_fSlideGain;

            CD2_LAYOUT_CHECKS(cPrismaticPropPrototype,
                CD2_SIZE(cPrismaticPropPrototype, 0x530)
                CD2_OFFSET(cPrismaticPropPrototype, m_fMinLinearLimit, 0x520)
                CD2_OFFSET(cPrismaticPropPrototype, m_fMaxLinearLimit, 0x524)
                CD2_OFFSET(cPrismaticPropPrototype, m_fSlideSpeed, 0x528)
                CD2_OFFSET(cPrismaticPropPrototype, m_fSlideGain, 0x52C))
        };
        static const Fun_Runtime::cClass *ms_pcPrismaticPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CPRISMATICPROP_H
