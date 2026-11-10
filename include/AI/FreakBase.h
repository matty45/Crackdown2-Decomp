#include "rws/attributes.h"
// AI::FreakBase (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824ABC68) is slot 11 of the vtable at 0x82109378, as cNonGameBase's RetClassName.
#ifndef AI_FREAKBASE_H
#define AI_FREAKBASE_H

#include "AI/cChaseBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace AI
{
    // RuffKing: AI::FreakPrototype : NPCBehaviourPrototype, 176 bytes. CD2's FreakBase::MakeNew (0x824ABC10) allocates
    // 0xB0 and calls this constructor (0x824B0B78), which calls NPCBehaviourPrototype's (0x824A8608).
    class FreakPrototype : public NPCBehaviourPrototype
    {
    public:
        FreakPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled90[0xB0 - 0x90];

        CD2_LAYOUT_CHECKS(FreakPrototype,
            CD2_SIZE(FreakPrototype, 0xB0))
    };

    class FreakBase : public AI::NPCBehaviourSM
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        FreakBase();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pFreakBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

    private:
        unsigned char m_unmodelledD0[0x120 - 0xD0];

        // CD2: FreakBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot89(); // 89: 0x824BAD88
    private:
        CD2_LAYOUT_CHECKS(FreakBase, CD2_SIZE(FreakBase, 0x120))
    };
}

#endif // AI_FREAKBASE_H
