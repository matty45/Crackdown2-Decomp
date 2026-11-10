// CD2 constructor 0x824AB1E0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/cNPCArmourySetup.h"
#include "AI/cPedestrianBase.h"
#include "gom/object_prototype.h"
#ifndef AI_PedestrianGuard_H
#define AI_PedestrianGuard_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "AI/cChaseBehaviour.h"
#include "cd2/layout.h"

namespace AI
{
    class PedestrianGuard : public AI::cPedestrianBase, public cNPCArmourySetup
    {
    public:
        // CD2 placement factory forwards only this; later reference builds add a prototype argument. CD2 0x824AB1E0,
        // out of line: cPedestrianBase's constructor (0x824A91F8), the class vptrs, then the words at 0x120 and 0x124.
        PedestrianGuard();

        // CD2's MakeNew (0x824AB020) allocates 0xA0, calls NPCBehaviourPrototype's constructor (0x824A8608) with the
        // packet, stores this prototype's vptrs (at 0 and 0x18) and clears the two flags below (names ours).
        class PedestrianGuardPrototype : public NPCBehaviourPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew.
            __forceinline PedestrianGuardPrototype(const RWS::CAttributePacket &packet)
                : NPCBehaviourPrototype(packet), m_bUnknown90(false), m_bUnknown91(false) {}

        private:
            bool m_bUnknown90; // 0x90
            bool m_bUnknown91; // 0x91
            unsigned char m_unmodelled92[0xA0 - 0x92];

            // CD2: PedestrianGuardPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824AB5D8
        private:
            CD2_LAYOUT_CHECKS(PedestrianGuardPrototype,
                CD2_SIZE(PedestrianGuardPrototype, 0xA0)
                CD2_OFFSET(PedestrianGuardPrototype, m_bUnknown90, 0x90))
        };
        // CD2 spawning initializer 0x82F92EA0 names placement factory 0x824ab0b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pPedestrianGuardClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        unsigned int m_nUnknown120; // 0x120 (name ours)
        unsigned int m_nUnknown124; // 0x124 (name ours)
        unsigned char m_unmodelled128[0x130 - 0x128];

        // 0x130: the size the class registrar gives.
        // CD2: PedestrianGuard's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824AB4D0
    private:
        CD2_LAYOUT_CHECKS(PedestrianGuard,
            CD2_SIZE(PedestrianGuard, 0x130)
            CD2_OFFSET(PedestrianGuard, m_nUnknown120, 0x120)
            CD2_OFFSET(PedestrianGuard, m_nUnknown124, 0x124))
    };
}

#endif
