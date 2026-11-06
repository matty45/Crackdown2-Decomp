#include "gom/object_prototype.h"
#ifndef AI_CPKDROPPILOT_H
#define AI_CPKDROPPILOT_H

#include "gom/non_game_base.h"
#include "AI/cPilotBase.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cTacticalObjective;

    // Base cPilotBase (CD2's inheritance registrar). The placement factory (0x824D4B88) inlines this class's constructor
    // over cPilotBase's (0x824D32E0) and zeroes the fields below; names and order are RuffKing's (0x30 lower in CD2).
    class cPKDropPilot : public AI::cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9C6A8 names placement factory 0x824d4b88.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPKDropPilotClass;

        __forceinline cPKDropPilot() : m_pTOMission(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        cTacticalObjective *m_pTOMission;    // 0x140
        unsigned char m_unmodelled144[0x150 - 0x144];

        CD2_LAYOUT_CHECKS(cPKDropPilot,
            CD2_SIZE(cPKDropPilot, 0x150)
            CD2_OFFSET(cPKDropPilot, m_pTOMission, 0x140))
    };
}

#endif

