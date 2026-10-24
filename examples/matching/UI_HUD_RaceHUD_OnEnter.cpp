// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x821E6878, 80 bytes
// Author : Opus 5.5 (manual pilot), 1 attempt
// Notes  : UI::HUD::RaceHUD::OnEnter. CD2 fetches localised strings through a manager instance; RuffKing later changed this to a free function, so its code was only a guide.
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

// Pilot: UI::HUD::RaceHUD::OnEnter  (CD2 0x821E6878, RuffKing 0x82AC9478)
// CD2 predates RuffKing's free-function Fun_Runtime::RetLocString; it goes through a manager instance.
class CLocalisedStringManager
{
public:
    static CLocalisedStringManager *Instance();
    const wchar_t *RetLocString(unsigned int nID);
};

namespace UI
{
    class Component
    {
    public:
        enum eOperation { };
        void SetVariable(const char *pName, const wchar_t *pString, int nMovieID);
        virtual void OnEnter(eOperation kOperation);
    };

    namespace HUD
    {
        class RaceHUD : public Component
        {
        public:
            virtual void OnEnter(eOperation kOperation);
        };

        void RaceHUD::OnEnter(eOperation kOperation)
        {
            SetVariable("RH_Lap.text", CLocalisedStringManager::Instance()->RetLocString(0xC3D7AE1E), 0);
        }
    }
}

