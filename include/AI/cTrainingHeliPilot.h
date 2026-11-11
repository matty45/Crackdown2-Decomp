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
        // CD2 table 0x8210CC48 has 123 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf115(); // primary slot 115
        virtual void vf116(); // primary slot 116
        virtual void vf117(); // primary slot 117
        virtual void vf118(); // primary slot 118
        virtual void vf119(); // primary slot 119
        virtual void vf120(); // primary slot 120
        virtual void vf121(); // primary slot 121
        virtual void vf122(); // primary slot 122

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

        // CD2: cTrainingHeliPilot's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824D63A0
    private:
        CD2_LAYOUT_CHECKS(cTrainingHeliPilot,
            CD2_SIZE(cTrainingHeliPilot, 0x150)
            CD2_OFFSET(cTrainingHeliPilot, m_pTrainingMission, 0x140)
            CD2_OFFSET(cTrainingHeliPilot, m_pPatrolEventHandle, 0x144))

    public:
        // CD2 table 0x8210CC48 differs from cPilotBase at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824D5508
        virtual void OnExit(); // slot 69: 0x824D5578
        virtual void Slot71(); // slot 71: 0x824D5818
        virtual void vf100(); // slot 100: 0x824D62E8
        virtual void vf106(); // slot 106: 0x824D5938
        virtual void vf110(); // slot 110: 0x824D04B8
        virtual void vf113(); // slot 113: 0x824D55C8
        virtual void vf114(); // slot 114: 0x824D5790
    };
}

#endif

