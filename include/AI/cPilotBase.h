// CD2 constructor 0x824D32E0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#ifndef AI_CPILOTBASE_H
#define AI_CPILOTBASE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cPilotBase : public AI::NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F9BE38 names placement factory 0x824d31b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPilotBaseClass;

        cPilotBase();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        // Own fields not recovered; 0x140 is the size its registrar and descriptor give (derived pilots start there).
        unsigned char m_unmodelledC0[0x140 - 0xC0];

        // CD2: cPilotBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824D3DE0
    private:
        CD2_LAYOUT_CHECKS(cPilotBase, CD2_SIZE(cPilotBase, 0x140))
    };
}

#endif

