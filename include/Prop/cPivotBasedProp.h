// Prop::cPivotBasedProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8273AED8) is slot 11 of the vtable at 0x8213FEB8, as cNonGameBase's RetClassName.
#ifndef PROP_CPIVOTBASEDPROP_H
#define PROP_CPIVOTBASEDPROP_H

#include "Prop/cProp.h"
#include "fun_runtime/vec3.h"

namespace Prop
{
    class cPivotBasedProp : public Prop::cProp
    {
    public:
        // CD2 0x823616B8: restores this class's vtables (primary 0x8213FEB8), then calls cProp's destructor.
        virtual ~cPivotBasedProp();
        // CD2 placement factory 0x8273AEE8; RuffKing signature.
        cPivotBasedProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing's prototype layout; CD2 factory 0x8273AE80 confirms size 0x520
        // and calls the out-of-line prototype constructor at 0x8273B208.
        class cPivotBasedPropPrototype : public cProp::cPropPrototype
        {
        public:
            cPivotBasedPropPrototype(const RWS::CAttributePacket &);
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            Fun_Runtime::Vec3 m_vecPivot;
            Fun_Runtime::Vec3 m_vecHingeAxis;
            Fun_Runtime::Vec3 m_vecPerpAxis;

            CD2_LAYOUT_CHECKS(cPivotBasedPropPrototype,
                CD2_SIZE(cPivotBasedPropPrototype, 0x520)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecPivot, 0x4F0)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecHingeAxis, 0x500)
                CD2_OFFSET(cPivotBasedPropPrototype, m_vecPerpAxis, 0x510))
        };
        static const Fun_Runtime::cClass *ms_pcPivotBasedPropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CPIVOTBASEDPROP_H
