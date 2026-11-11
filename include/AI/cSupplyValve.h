#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::cSupplyValve (Crackdown 2): STAND-IN for the class name only. Base Prop::cSpinningProp, as in RuffKing's header;
// RetClassName (0x82457C10) is slot 11 of the vtable at 0x82102438, as cNonGameBase's RetClassName.
#ifndef AI_CSUPPLYVALVE_H
#define AI_CSUPPLYVALVE_H

#include "Prop/cSpinningProp.h"

namespace AI
{
    class cSupplyValve : public Prop::cSpinningProp
    {
    public:
        // Name and base from RuffKing (1344 bytes); CD2 slot 5 at 0x82457DE0. CD2's MakeNew (0x82457BA0) allocates
        // 0x540, calls cSpinningPropPrototype's constructor (0x8273F5C0) and stores this class's vptrs: the constructor
        // is inline and initializes none of its own fields, which are not recovered.
        class cSupplyValvePrototype : public Prop::cSpinningProp::cSpinningPropPrototype
        {
        public:
            __forceinline cSupplyValvePrototype(const RWS::CAttributePacket &packet)
                : Prop::cSpinningProp::cSpinningPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled530[0x540 - 0x530];

            CD2_LAYOUT_CHECKS(cSupplyValvePrototype,
                CD2_SIZE(cSupplyValvePrototype, 0x540))
        };

        // CD2 spawning initializer 0x82F866D0 names placement factory 0x82457c20.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSupplyValveClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x822C8900.
        virtual ~cSupplyValve();
        // CD2: cSupplyValve's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot20(); // 20: 0x823ABEF8
        virtual void vf76(); // 76: 0x824585F8
        virtual void vf78(); // 78: 0x8288FB78
        virtual void vf79(); // 79: 0x82457F00
        virtual void vf80(); // 80: 0x82457F78
        virtual void vf82(); // 82: 0x82457FE0
        virtual void vf83(); // 83: 0x824581A0
        virtual void vf84(); // 84: 0x82458248
        virtual void vf335(); // 335: 0x82458618

    public:
        // CD2 table 0x82102438 differs from cSpinningProp at these inherited slots.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // slot 18: 0x82457ED0
    };
}

#endif // AI_CSUPPLYVALVE_H
