// STAND-IN for the HUD opacity setting. RuffKing UI::SetHUDOpacity supplies the
// name and clamping behavior; CD2 ApplyHUDOpacity stores 0x83092608.
#ifndef UI_UI_H
#define UI_UI_H

extern int g_iHUDOpacity;

namespace UI
{
    inline int SetHUDOpacity(int percent)
    {
        if (percent < 0)
            percent = 0;
        else if (percent > 100)
            percent = 100;
        g_iHUDOpacity = percent;
        return percent;
    }
}
#endif
