#include "gom/object_prototype.h"
#ifndef AI_CTRAININGHELIPILOT_H
#define AI_CTRAININGHELIPILOT_H

#include "gom/non_game_base.h"
#include "AI/cPilotBase.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cTrainingMission;
    class cAIEventSubscription;

    // Base cPilotBase (CD2's inheritance registrar). The placement factory (0x824D5350) inlines this class's constructor
    // over cPilotBase's (0x824D32E0) and zeroes the fields below; names and order are RuffKing's (0x30 lower in CD2).
    class cTrainingHeliPilot : public AI::cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9CAE0 names placement factory 0x824d5350.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingHeliPilotClass;

        __forceinline cTrainingHeliPilot() : m_pTrainingMission(0), m_pPatrolEventHandle(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
        cTrainingMission *m_pTrainingMission; // 0x140
        cAIEventSubscription *m_pPatrolEventHandle; // 0x144
        unsigned char m_unmodelled148[0x150 - 0x148];

        CD2_LAYOUT_CHECKS(cTrainingHeliPilot,
            CD2_SIZE(cTrainingHeliPilot, 0x150)
            CD2_OFFSET(cTrainingHeliPilot, m_pTrainingMission, 0x140)
            CD2_OFFSET(cTrainingHeliPilot, m_pPatrolEventHandle, 0x144))
    };
}

#endif

