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
        // CD2 0x8273EB20: restores this class's vtables, then calls cPivotBasedProp's destructor.
        virtual ~cSpinningProp();
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
        // CD2: cSpinningProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8273EE70
        virtual void Slot13(); // 13: 0x8273EDE0
        virtual void vf271(); // 271: 0x8273EED8
        virtual void vf283(); // 283: 0x8273EF58
        virtual void vf314(); // 314: 0x8273EEC8
        virtual void vf317(); // 317: 0x8273EF18
        virtual void vf320(); // 320: 0x827E56A8
        virtual void CreateConstraintData(); // 341: 0x8273F000
        virtual void DestroyConstraintData(); // 342: 0x8273F250
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8273FA38
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8273FA50
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x82457AD8

    public:
        // CD2 table 0x82141860 differs from cPivotBasedProp at these inherited slots.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // slot 18: 0x8273EBD8
    };
}

#endif // PROP_CSPINNINGPROP_H
