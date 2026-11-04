// AI::cPilotBase (Crackdown 2): STAND-IN. Size 0x140 (its registrar); its constructor 0x824D32E0 calls NPCBehaviour's
// (0x824A89C8). Fields not modelled.
#ifndef AI_CPILOTBASE_H
#define AI_CPILOTBASE_H

#include "gom/object_prototype.h"
#include "AI/NPCBehaviour.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cPilotBase : public NPCBehaviour
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPilotBaseClass;

    private:
        unsigned char m_padC0[0x140 - 0xC0];

    public:
        // Out of line: CD2 0x824D32E0 (SpawnFromPrototype tail-calls it); it first calls NPCBehaviour's 0x824A89C8.
        cPilotBase();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(cPilotBase,
            CD2_SIZE(cPilotBase, 0x140))
    };
}

#endif

