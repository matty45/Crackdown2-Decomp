// Activity::cSquadSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823DD810, MakeNew 0x823DD8B0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSquadSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar. Fields: RuffKing's names and order, 0x40 below its
// offsets as for the squad member points (cSquadMemberSpawnPointBase.h); they end at 0x1D0, the size CD2's registrar
// gives (RuffKing's 0x210 less 0x40).
#ifndef ACTIVITY_CSQUADSPAWNPOINT_H
#define ACTIVITY_CSQUADSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"
#include "editor/guid_event_handler.h"
#include "fun_runtime/pointer_list.h"
#include "fun_runtime/vectorip.h"

namespace AI { class cMissionCriticalPropSpawnPoint; class cMissionBase; }

namespace Activity
{
    class cSquadMemberSpawnPoint;

    class cSquadSpawnPoint : public cSpawnPointBase
    {
    public:
        // CD2 0x823DD7A0 / 0x823DD7B0: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSquadSpawnPointClass;
        // CD2 0x823DD910; MakeNew applies the packet afterwards.
        cSquadSpawnPoint();
        virtual cNonGameBase *Spawn();

    protected:
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
    private:
        Fun_Runtime::cVectorip<cSquadMemberSpawnPoint *, 32> m_vMembers;
        Fun_Runtime::cPointerList<AI::cMissionCriticalPropSpawnPoint *> m_lTargetProps;
        AI::cMissionCriticalPropSpawnPoint *m_pCurrentTarget;
        AI::cMissionBase *m_pMission;
        Fun_Runtime::cVectorip<GOM::cObjectPrototype *, 32> m_vPrototypes;
        unsigned char m_nProtoSpawnIndex;
        Editor::cGUIDEventHandler<cSquadSpawnPoint> m_EventHandler;
        unsigned int m_nDeathMask;
        unsigned int m_nSpawnMask;
        unsigned int m_nAISpawnMask;
        unsigned int m_nAIRespawnMask;
        bool m_bRespawnersAttached;
        bool m_bNoInitialSpawn;
        bool m_bAtomicSpawnAndSquadManagement;
        bool m_bSquadDisabledByMission;
        float m_fSpawnTimer;
        float m_fInitialSpawnTimer;
        unsigned int m_nNumRespawn;
        unsigned int m_nMaxNumRespawn;
        bool m_bInfiniteRespawn;
        bool m_bHasInfiniteRespawners;
        bool m_bPropTargetCompulsory;
        bool m_bBreakUpOnDeath;

        CD2_LAYOUT_CHECKS(cSquadSpawnPoint,
            CD2_SIZE(cSquadSpawnPoint, 0x1D0)
            CD2_OFFSET(cSquadSpawnPoint, m_vMembers, 0x50)
            CD2_OFFSET(cSquadSpawnPoint, m_lTargetProps, 0xE0)
            CD2_OFFSET(cSquadSpawnPoint, m_vPrototypes, 0x100)
            CD2_OFFSET(cSquadSpawnPoint, m_EventHandler, 0x194)
            CD2_OFFSET(cSquadSpawnPoint, m_bBreakUpOnDeath, 0x1CF))
    };
}

#endif // ACTIVITY_CSQUADSPAWNPOINT_H
