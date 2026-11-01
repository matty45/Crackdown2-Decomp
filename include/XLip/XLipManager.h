// STAND-IN interface only; no objects are constructed or accessed through this layout.
// Names/signatures: RuffKing XLipManager.h and UI::ApplyVOSetting. CD2's corresponding
// callback calls GetInstance (0x82885CA0), then SetUseOriginalAudio (0x823ABE68).
#ifndef XLIP_XLIPMANAGER_H
#define XLIP_XLIPMANAGER_H

namespace XLip
{
    class XLipManager
    {
    public:
        static XLipManager *GetInstance();
        void SetUseOriginalAudio(bool flag);
    };
}

#endif
