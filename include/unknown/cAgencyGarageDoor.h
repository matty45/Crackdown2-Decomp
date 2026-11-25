#include "gom/object_prototype.h"
#ifndef unknown_cAgencyGarageDoor_H
#define unknown_cAgencyGarageDoor_H

#include "rws/attributes.h"
#include "Prop/cPrismaticProp.h"
#include "Prop/cSlidingDoor.h"
#include "fun_runtime/class.h"

namespace unknown
{
    // Base cSlidingDoor: its inheritance registrar (0x82FF67B0) names it and its destructor (0x82733050) calls
    // cSlidingDoor's. That destructor also clears two statics and restores the vptr of cSlidingDoor's cPathObjectOwner.
    class cAgencyGarageDoor : public Prop::cSlidingDoor
    {
    public:
        // Prototype name ours. CD2's MakeNew (0x82732DC0) allocates 0x540, calls cPrismaticPropPrototype's constructor
        // (0x8273CBD0), stores this class's vptrs and -1 at 0x530: the constructor is inline. The word's name is ours.
        class cAgencyGarageDoorPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            __forceinline cAgencyGarageDoorPrototype(const RWS::CAttributePacket &packet)
                : Prop::cPrismaticProp::cPrismaticPropPrototype(packet), m_n530(-1) {}

            int m_n530;

            // CD2: cAgencyGarageDoorPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x827349A0
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82734A50
        public:
            CD2_LAYOUT_CHECKS(cAgencyGarageDoorPrototype,
                CD2_SIZE(cAgencyGarageDoorPrototype, 0x540)
                CD2_OFFSET(cAgencyGarageDoorPrototype, m_n530, 0x530))
        };

        // CD2 spawning initializer 0x82FF6868 names placement factory 0x82732e48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82732F00: the placement factory (0x82732E48) calls it out of line with the prototype.
        cAgencyGarageDoor(GOM::cObjectPrototype *);
        static const Fun_Runtime::cClass *ms_pcAgencyGarageDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2 0x82732D50 / 0x82732D60: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // The slots where CD2's table (0x82012DF0, stored by the constructor) differs from cSlidingDoor's; names and
        // signatures are the bases'. 76 holds a shared float getter body (folded).
        virtual ~cAgencyGarageDoor(); // 0: 0x82733000
        virtual bool EnterPhysicalState(); // 7: 0x82733128
        virtual void Slot13(); // 13: 0x82734890
        virtual void TickUpdate(float dt); // 23: 0x827338E8
        virtual bool EnterRenderableState(eResourcesType eResources); // 31: 0x827331E0
        virtual void LeaveRenderableState(); // 32: 0x827332E0
        virtual void vf76(); // 76: 0x82457958
        virtual void vf140(); // 140: 0x827333B8
        virtual void vf158(); // 158: 0x827331C8

    private:
        // The constructor (0x82732F00) stores this in the first and clears the second; the destructor (0x82733050) clears
        // both. Names ours.
        static cAgencyGarageDoor *ms_pInstance;             // 0x83800FA4
        static bool ms_bUnknown;                            // 0x83800F9D
        // Fields the constructor clears; names ours.
        unsigned int m_nUnknownF00;
        unsigned int m_nUnknownF04;
        unsigned char m_unknownF08[0xF10 - 0xF08];
        float m_fUnknownF10;
        float m_fUnknownF14;
        float m_fUnknownF18;
        unsigned char m_unknownF1C[0xF21 - 0xF1C];
        bool m_bUnknownF21;
        float m_fUnknownF24;

        CD2_LAYOUT_CHECKS(cAgencyGarageDoor,
            CD2_SIZE(cAgencyGarageDoor, 0xF30)
            CD2_OFFSET(cAgencyGarageDoor, m_nUnknownF00, 0xF00)
            CD2_OFFSET(cAgencyGarageDoor, m_fUnknownF10, 0xF10)
            CD2_OFFSET(cAgencyGarageDoor, m_bUnknownF21, 0xF21)
            CD2_OFFSET(cAgencyGarageDoor, m_fUnknownF24, 0xF24))
    };
}

#endif
