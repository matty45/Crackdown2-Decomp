// STAND-IN for the two session options used by UIControl. Names are from RuffKing's
// SetUsingSubtitles/SetControllerInvert; CD2's callbacks store 0x83800A47/0x83800A45.
#ifndef SESSION_GAMESESSION_H
#define SESSION_GAMESESSION_H

namespace Session
{
    extern bool g_isUsingSubtitles;
    extern bool g_isControllerInvert;

    inline void SetUsingSubtitles(bool value) { g_isUsingSubtitles = value; }
    inline void SetControllerInvert(bool value) { g_isControllerInvert = value; }
}

#endif
