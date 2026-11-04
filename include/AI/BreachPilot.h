// AI::BreachPilot (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824D16E0) calls cPilotBase's constructor (0x824D32E0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_BREACHPILOT_H
#define AI_BREACHPILOT_H

#include "AI/cPilotBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class BreachPilot : public cPilotBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pBreachPilotClass;

    private:
        unsigned int m_nUnknown140; // 0x140
        unsigned int m_nUnknown144; // 0x144
        unsigned int m_nUnknown148; // 0x148
        unsigned char m_pad14C[0x150 - 0x14C];
        Fun_Runtime::Vec3 m_vUnknown150; // 0x150 (default-constructed: x, y, z = 0)

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline BreachPilot() : m_nUnknown140(0), m_nUnknown144(0), m_nUnknown148(0) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(BreachPilot,
            CD2_SIZE(BreachPilot, 0x160)
            CD2_OFFSET(BreachPilot, m_nUnknown140, 0x140))
    };
}

#endif

