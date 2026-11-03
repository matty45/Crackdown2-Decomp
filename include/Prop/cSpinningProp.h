// Prop::cSpinningProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x8273E670) is slot 11 of the vtable at 0x82141860, as cNonGameBase's RetClassName.
#ifndef PROP_CSPINNINGPROP_H
#define PROP_CSPINNINGPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cSpinningProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 placement factory 0x8273E680; constructor signature follows RuffKing.
        cSpinningProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing layout; CD2 factory 0x8273E618 allocates 0x530 and calls constructor 0x8273F5C0.
        class cSpinningPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cSpinningPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fSpinSpeed;
            float m_fSpinAccel;

            CD2_LAYOUT_CHECKS(cSpinningPropPrototype,
                CD2_SIZE(cSpinningPropPrototype, 0x530)
                CD2_OFFSET(cSpinningPropPrototype, m_fSpinSpeed, 0x520)
                CD2_OFFSET(cSpinningPropPrototype, m_fSpinAccel, 0x524))
        };
        static const Fun_Runtime::cClass *ms_pcSpinningPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CSPINNINGPROP_H
