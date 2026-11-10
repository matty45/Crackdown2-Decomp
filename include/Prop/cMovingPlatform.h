// Prop::cMovingPlatform (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x8273A838) is slot 11 of the vtable at 0x8213F800, as cNonGameBase's RetClassName.
#ifndef PROP_CMOVINGPLATFORM_H
#define PROP_CMOVINGPLATFORM_H

#include "Prop/cProp.h"

namespace Prop
{
    class cMovingPlatform : public Prop::cProp
    {
    public:
        // Prototype interface from RuffKing; CD2 slot 5 at 0x8273ADA0. Instance fields are not modelled.
        class cMovingPlatformPrototype : public cProp::cPropPrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 placement factory 0x8273A848; constructor signature follows RuffKing.
        cMovingPlatform(GOM::cObjectPrototype *);
        // CD2 destructor 0x8273AA30 only restores the vtables and calls cProp's destructor.
        virtual ~cMovingPlatform();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMovingPlatformClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2: cMovingPlatform's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8273ACC8
        virtual bool EnterPhysicalState(); // 7: 0x8273AD28
        virtual void Slot13(); // 13: 0x82732350
        virtual void Slot23(); // 23: 0x8273AD20
        virtual void Slot27(); // 27: 0x8273AD98
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x8273AAE8
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8273AE08
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8273ADB0
        // CD2: cMovingPlatform's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void vf272(); // 272: 0x82686318
    };
}

#endif // PROP_CMOVINGPLATFORM_H
