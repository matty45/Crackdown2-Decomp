#include "gom/object_prototype.h"
#include "rws/attributes.h"
// AI::Goliath (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824B0F18) is slot 11 of the vtable at 0x821096A0, as cNonGameBase's RetClassName.
#ifndef AI_GOLIATH_H
#define AI_GOLIATH_H

#include "AI/cChaseBehaviour.h"
#include "fun_runtime/vec3.h"
#include "cd2/layout.h"

namespace AI
{
    // RuffKing: AI::GoliathPrototype : NPCBehaviourPrototype, 144 bytes. CD2's Goliath::MakeNew (0x824B0EA8) allocates
    // 0x90, calls NPCBehaviourPrototype's constructor (0x824A8608) and stores this class's vptrs; its table
    // (0x82109670) overrides slot 1 with 0x824B2560.
    class GoliathPrototype : public NPCBehaviourPrototype
    {
    public:
        __forceinline GoliathPrototype(const RWS::CAttributePacket &packet) : NPCBehaviourPrototype(packet) {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        CD2_LAYOUT_CHECKS(GoliathPrototype,
            CD2_SIZE(GoliathPrototype, 0x90))
    };

    class Goliath : public AI::NPCBehaviourSM
    {
    public:
        // CD2 spawning initializer 0x82F93B58 names placement factory 0x824b0f28.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pGoliathClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (0x824B0F28), which calls
        // NPCBehaviourSM's constructor (0x824ABA30) out of line and then initialises the fields below (names ours).
        __forceinline Goliath()
            : m_nUnknownE0(0), m_nUnknownE4(-1), m_nUnknownE8(0), m_nUnknownEC(0), m_nUnknownF0(0), m_fUnknownF4(0.0f) {}

    private:
        Fun_Runtime::Vec3 m_vUnknownD0; // 0xD0
        unsigned int m_nUnknownE0;      // 0xE0
        short m_nUnknownE4;             // 0xE4
        unsigned int m_nUnknownE8;      // 0xE8
        unsigned int m_nUnknownEC;      // 0xEC
        unsigned int m_nUnknownF0;      // 0xF0
        float m_fUnknownF4;             // 0xF4
        unsigned char m_unmodelledF8[0x100 - 0xF8];

        // 0x100: the size Goliath's class registrar gives.
        CD2_LAYOUT_CHECKS(Goliath,
            CD2_SIZE(Goliath, 0x100)
            CD2_OFFSET(Goliath, m_vUnknownD0, 0xD0)
            CD2_OFFSET(Goliath, m_nUnknownE4, 0xE4)
            CD2_OFFSET(Goliath, m_fUnknownF4, 0xF4))
    };
}

#endif // AI_GOLIATH_H
