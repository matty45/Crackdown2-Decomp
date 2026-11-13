#include "AI/cMission.h"
// Mission base restored from the registered parent and reference hierarchy; instance fields remain incomplete.
#ifndef AI_CFINALMISSION_H
#define AI_CFINALMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cFinalMission : public AI::cMission
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcFinalMissionClass;

        cFinalMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cFinalMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x8246D070
        virtual void OnClientMissionStateNotification(unsigned char,unsigned char); // cRegisteredClass 15: 0x8246C340
        virtual void OnChildMissionCompleted(AI::cMission *); // cRegisteredClass 22: 0x8246C238
        virtual bool ArePrerequisitesComplete() const; // cRegisteredClass 23: 0x8246E5E8
        virtual bool IsLocalPlayerNearby() const; // cRegisteredClass 24: 0x8246E5F8
        virtual void InitReplication(); // cRegisteredClass 37: 0x8246BDD0
        virtual void TermReplication(); // cRegisteredClass 38: 0x8246BEE0
    protected:
        virtual void OnLeaveMissionState(unsigned char); // cRegisteredClass 29: 0x8246CC98
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x8246CA40
        virtual void OnEnterGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 33: 0x8246C248
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x8246C430
        // RuffKing's first cFinalMission fields (cFinalMission.h) at CD2's offsets: OnChildMissionCompleted (0x8246C238)
        // counts 0x3C5. Size 0xC50 from CD2's registrar; RuffKing's class is smaller, so the rest is not modelled.
        void *m_pActivationZone; // RuffKing: cHeliCallZone *
        unsigned char m_nNumChildMissions;
        unsigned char m_nNumChildMissionsCompleted;
        unsigned char m_unmodelled3C6[2];
        unsigned int m_unmodelled3C8[(0xC50 - 0x3C8) / 4];
        CD2_LAYOUT_CHECKS(cFinalMission,
            CD2_OFFSET(cFinalMission, m_nNumChildMissionsCompleted, 0x3C5)
            CD2_SIZE(cFinalMission, 0xC50))
    };
}

#endif

