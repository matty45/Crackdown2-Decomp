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
    // cSlidingDoor's. That destructor also clears two statics and restores a vptr at +0xED0 (an interface not modelled).
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
    };
}

#endif
