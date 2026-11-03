// Prop::cHingedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cPivotBasedProp, as in RuffKing's
// header; RetClassName (0x82736E40) is slot 11 of the vtable at 0x8213E830, as cNonGameBase's RetClassName.
#ifndef PROP_CHINGEDPROP_H
#define PROP_CHINGEDPROP_H

#include "Prop/cPivotBasedProp.h"

namespace Prop
{
    class cHingedProp : public Prop::cPivotBasedProp
    {
    public:
        // CD2 placement factory 0x82736E50; RuffKing signature.
        cHingedProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing fields; CD2's factory allocates 0x530 and invokes the constructor
        // at 0x82738740, also called by cHingedDoor's prototype factory.
        class cHingedPropPrototype : public cPivotBasedProp::cPivotBasedPropPrototype
        {
        public:
            cHingedPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            float m_fMinAngle;
            float m_fMaxAngle;
            bool m_RotFreeAtStart;
            bool m_bFlipHinge;

            CD2_LAYOUT_CHECKS(cHingedPropPrototype,
                CD2_SIZE(cHingedPropPrototype, 0x530)
                CD2_OFFSET(cHingedPropPrototype, m_fMinAngle, 0x520)
                CD2_OFFSET(cHingedPropPrototype, m_fMaxAngle, 0x524)
                CD2_OFFSET(cHingedPropPrototype, m_RotFreeAtStart, 0x528)
                CD2_OFFSET(cHingedPropPrototype, m_bFlipHinge, 0x529))
        };
        static const Fun_Runtime::cClass *ms_pcHingedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CHINGEDPROP_H
