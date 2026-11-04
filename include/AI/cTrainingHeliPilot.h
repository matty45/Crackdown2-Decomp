// AI::cTrainingHeliPilot (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824D5350) calls cPilotBase's constructor (0x824D32E0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CTRAININGHELIPILOT_H
#define AI_CTRAININGHELIPILOT_H

#include "AI/cPilotBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cTrainingHeliPilot : public cPilotBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingHeliPilotClass;

    private:
        unsigned int m_nUnknown140; // 0x140
        unsigned int m_nUnknown144; // 0x144
        unsigned char m_pad148[0x150 - 0x148];

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline cTrainingHeliPilot() : m_nUnknown140(0), m_nUnknown144(0) {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(cTrainingHeliPilot,
            CD2_SIZE(cTrainingHeliPilot, 0x150)
            CD2_OFFSET(cTrainingHeliPilot, m_nUnknown140, 0x140))
    };
}

#endif

