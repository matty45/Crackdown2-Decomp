// Prop::cSearchLight (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82745760) is slot 11 of the vtable at 0x821441D8, as cNonGameBase's RetClassName.
#ifndef PROP_CSEARCHLIGHT_H
#define PROP_CSEARCHLIGHT_H

#include "Prop/cProp.h"
#include "fun_runtime/retval.h"

namespace Prop
{
    class cSearchLight : public Prop::cProp
    {
    public:
        // CD2 0x827459D8 only restores vtables and invokes cProp's destructor.
        virtual ~cSearchLight();
        // CD2 placement factory 0x82745770; RuffKing signature.
        cSearchLight(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing names; CD2 MakeNew (0x827456D8) zeroes four floats at 0x4F0..0x4FC.
        class cSearchLightPrototype : public cProp::cPropPrototype
        {
        public:
            cSearchLightPrototype(const RWS::CAttributePacket &packet)
                : cPropPrototype(packet), m_fMaxRotX(0), m_fMaxRotY(0),
                  m_fDegreesPerSecondX(0), m_fDegreesPerSecondY(0) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);
        protected:
            float m_fMaxRotX;
            float m_fMaxRotY;
            float m_fDegreesPerSecondX;
            float m_fDegreesPerSecondY;

            CD2_LAYOUT_CHECKS(cSearchLightPrototype,
                CD2_SIZE(cSearchLightPrototype, 0x500)
                CD2_OFFSET(cSearchLightPrototype, m_fMaxRotX, 0x4F0)
                CD2_OFFSET(cSearchLightPrototype, m_fMaxRotY, 0x4F4)
                CD2_OFFSET(cSearchLightPrototype, m_fDegreesPerSecondX, 0x4F8)
                CD2_OFFSET(cSearchLightPrototype, m_fDegreesPerSecondY, 0x4FC))
        };
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSearchLightClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2: cSearchLight's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x8272A070
        virtual void Slot14(); // 14: 0x82745A90
        virtual void Slot23(); // 23: 0x82745B98
    };
}

#endif // PROP_CSEARCHLIGHT_H
