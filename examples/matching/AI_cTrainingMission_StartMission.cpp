// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x82480DA0, 88 bytes
// Author : Opus 5.5 (manual pilot), 1 attempt
// Notes  : AI::cTrainingMission::StartMission. Class layout from the RuffKing PDB (cMission base 0x3C0 bytes, RWS::CEventHandler at 0x3C0).
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

// Pilot: AI::cTrainingMission::StartMission  (CD2 0x82480DA0, RuffKing 0x823DFB38)
namespace RWS
{
    class CEventId
    {
        unsigned int m_id;
    };

    extern CEventId iMsgRestartPlayer;

    class CEventHandler
    {
    public:
        void LinkMsg(CEventId &Id, const char *pFormat, unsigned short priority);
    };
}

namespace AI
{
    class cMission
    {
    protected:
        void SetMissionState(unsigned char nMissionState, bool bAllowAutoSave);
        char m_pad[0x3C0];
    };

    class cTrainingMission : public cMission, public RWS::CEventHandler
    {
        void StopMission();
        void StartMission();
    };

    void cTrainingMission::StartMission()
    {
        StopMission();
        SetMissionState(0, true);
        LinkMsg(RWS::iMsgRestartPlayer, "Mtx *", 0x8000);
    }
}

