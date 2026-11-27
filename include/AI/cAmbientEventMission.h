#include "AI/cMissionBase.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "fun_runtime/vectorip.h"
// AI::cAmbientEventMission (Crackdown 2): RuffKing's bases, virtuals and fields. The event handler comes first: its
// table (0x82105A18, the deleting destructor in slot 0) is the primary one, and cMissionBase follows at +0x10. CD2's
// destructor (0x8248DBD0) unlinks the dawn and dusk messages through +0, then calls ~cMissionBase (0x8245A8D0) on +0x10
// and ~CEventHandler. RuffKing's field offsets are CD2's: the in-place mission vector ends at 0x3B0, the size
// StaticCreateClass (0x8248DAE0) gives.
#ifndef AI_CAMBIENTEVENTMISSION_H
#define AI_CAMBIENTEVENTMISSION_H

#include "fun_runtime/class.h"

namespace AI
{
    class cMission;

    class cAmbientEventMission : public RWS::CEventHandler, public AI::cMissionBase
    {
    public:
        // Out of line: CD2 0x822AC158 (MakeNew calls it).
        cAmbientEventMission();
        virtual ~cAmbientEventMission();
        // RuffKing's new virtuals, in its order: CD2's primary table 0x82105A18, slots 6 to 9.
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void InitReplication();
        virtual void TermReplication();
        // CD2 0x8248DA20 / 0x8248DA30: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAmbientEventMissionClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        // RuffKing's overrides. CD2's tables hold this class's code for them, or a body it shares with other classes:
        // CEventHandler slot 5 (0x8248DC80); cMissionBase's primary slots 2, 3, 4 (empty), 8 and 9; cReplicatedClass
        // slots 3 (0x82709328, cMission's), 8, 9, 14 (0x8283D658), 16 (return 8), 22 (return 11) and 23 (return 1);
        // CAttributeHandler slot 1 (0x8248DFC0).
        virtual void HandleEvents(RWS::CMsg &pMsg);
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        virtual void TickUpdate(float dT);
        virtual void Activate();
        virtual void Deactivate();
        virtual void ResetMission() {}
        virtual unsigned short RetMissionID() const;
        virtual void CalculateLOD(int nNodeID);
        virtual bool IsOwnedLocally();
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
        virtual unsigned int GetNumObjectIDBits() const;
        virtual void ReplicateInitialFields();
        virtual void ReplicateFields();

        enum eAmbientEventDayState
        {
            eAES_Day1 = 0,
            eAES_Night1,
            eAES_Day2,
            eAES_Night2,
            eAES_Day3,
            eAES_Night3,
            eAES_Day1Clear,
            eAES_Night1Clear,
            eAES_Day2Clear,
            eAES_Night2Clear,
            eAES_Day3Clear,
            eAES_Night3Clear,
            eAES_NumStates,
            eAES_Invalid,
        };
        // RuffKing's (out of line there, 0x823F35E0): the next day state, wrapping back six past m_nMaxIndex. CD2 has
        // no copy: HandleEvents (0x8248DC80) expands it at both of its calls.
        void IncrementCount()
        {
            unsigned int nNewDayState = m_eDayState + 1;
            if (nNewDayState >= m_nMaxIndex)
                nNewDayState -= 6;
            SetAmbientEventDayState(static_cast<eAmbientEventDayState>(nNewDayState));
        }
    protected:
        // RuffKing's (out of line there, 0x823F3088); CD2 expands it in HandleEvents and ReplicateFields (0x8248E248).
        void SetAmbientEventDayState(eAmbientEventDayState eNewDayState)
        {
            if (m_eDayState != eNewDayState && eNewDayState <= eAES_Night3Clear)
            {
                m_eDayState = eNewDayState;
                SetSquadGroup(static_cast<etSquadGroup>(eNewDayState));
            }
        }
        // RuffKing's (out of line there, 0x823F3630); CD2 expands it in TickUpdate (0x8248E138): flips between the six
        // day states and their cleared forms.
        void ToggleCleared()
        {
            if (IsAuthority())
            {
                unsigned int nNewDayState = m_eDayState;
                m_bCleared = !m_bCleared;
                if (m_bCleared)
                {
                    m_nMaxIndex = 12;
                    nNewDayState += 6;
                }
                else
                {
                    m_nMaxIndex = 6;
                    nNewDayState -= 6;
                }
                SetAmbientEventDayState(static_cast<eAmbientEventDayState>(nNewDayState));
            }
        }
        enum etReplicatedFields
        {
            eRF_GlobalEventState = 0,
            eRF_NumEvents,
        };
    private:
        bool m_bCleared;
        unsigned char m_nMaxIndex;
        bool m_bIsDay;
        eAmbientEventDayState m_eDayState;
        Fun_Runtime::cVectorip<cMission *, 10> m_vMissions;

        CD2_LAYOUT_CHECKS(cAmbientEventMission,
            CD2_SIZE(cAmbientEventMission, 0x3B0)
            CD2_OFFSET(cAmbientEventMission, m_bCleared, 0x360)
            CD2_OFFSET(cAmbientEventMission, m_eDayState, 0x364)
            CD2_OFFSET(cAmbientEventMission, m_vMissions, 0x370))
    };
}

#endif // AI_CAMBIENTEVENTMISSION_H
