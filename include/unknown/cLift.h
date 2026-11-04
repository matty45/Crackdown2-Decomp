#include "cd2/layout.h"
#include "Prop/cPrismaticProp.h"
#include "rws/attributes.h"
// unknown::cLift (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82738F88) builds cClass(0x102B, "cLift", 0xF30); 0xF30 is the size its registrar gives.
#ifndef UNKNOWN_CLIFT_H
#define UNKNOWN_CLIFT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cLift
    {
    public:
        // CD2 MakeNew (0x82738E98) allocates 0x540 bytes, calls Prop::cPrismaticProp::cPrismaticPropPrototype's constructor with the packet, installs
        // this prototype's vtables (at 0 and 0x18) and initialises the fields below (names ours).
        class cLiftPrototype : public Prop::cPrismaticProp::cPrismaticPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cLiftPrototype(const RWS::CAttributePacket &packet)
                : Prop::cPrismaticProp::cPrismaticPropPrototype(packet), m_nUnknown530(-1), m_nUnknown534(-1), m_nUnknown538(-1) {}

        private:
            int m_nUnknown530; // 0x530
            int m_nUnknown534; // 0x534
            int m_nUnknown538; // 0x538
            unsigned char m_pad53C[0x540 - 0x53C];

            CD2_LAYOUT_CHECKS(cLiftPrototype,
                CD2_SIZE(cLiftPrototype, 0x540)
                CD2_OFFSET(cLiftPrototype, m_nUnknown530, 0x530))
        };

        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcLiftClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CLIFT_H
