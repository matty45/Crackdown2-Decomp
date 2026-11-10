// AI::cTacticalObjective (Crackdown 2): RuffKing cTacticalObjective.h gives the bases (CEventHandler, cMission) and
// the size 0x530, which CD2's registrar and StaticCreateClass (0x824759A8) confirm. CD2's constructor 0x82475A48
// stores CEventHandler's table at 0 and constructs cMission at +0x10 (0x824592E8). The primary table 0x821044A0 has
// CEventHandler's six slots, then HasBackupBeenCalled (6, 0x82475880, as in RuffKing). cMission's table at +0x10
// (0x820073D8) carries the mission overrides. Own fields (0x3D0..) are not modelled yet: cMission's are not.
#ifndef AI_CTACTICALOBJECTIVE_H
#define AI_CTACTICALOBJECTIVE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "AI/cMission.h"

namespace AI
{
    class cTacticalObjective : public RWS::CEventHandler, public cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcTacticalObjectiveClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        cTacticalObjective(const RWS::CAttributePacket &);
        virtual ~cTacticalObjective();
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void TickUpdate(float);
        virtual void ResetMission();
        virtual bool IsComplete() const;
        virtual bool HasBackupBeenCalled() const;
        virtual bool IsLocalPlayerNearby() const;
    };
}

#endif // AI_CTACTICALOBJECTIVE_H
