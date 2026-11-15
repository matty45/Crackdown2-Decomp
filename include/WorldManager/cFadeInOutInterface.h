// STAND-IN: reference standalone fade interface; CD2 LOD4 constructor 0x82807900
// initializes this 0x18-byte base at +0x120 with the reference field offsets.
#ifndef WORLDMANAGER_CFADEINOUTINTERFACE_H
#define WORLDMANAGER_CFADEINOUTINTERFACE_H
#include "cd2/layout.h"
namespace WorldManager
{
    enum eFadeState
    {
        eFS_Invisible, eFS_WaitingToFadeIn, eFS_FadeIn, eFS_FullyVisible, eFS_FadeOut, eFS_LOD4Fade
    };
    class cFadeInOutInterface
    {
    public:
        cFadeInOutInterface();
        virtual ~cFadeInOutInterface();
        eFadeState RetFadeState() const { return m_eFadeState; }
    private:
        cFadeInOutInterface *m_pReplacing;
        cFadeInOutInterface *m_pReplacedBy;
        unsigned int m_nFadeStartTime;
        eFadeState m_eFadeState;
        eFadeState m_ePreviousFadeState;
        CD2_LAYOUT_CHECKS(cFadeInOutInterface,
            CD2_SIZE(cFadeInOutInterface, 0x18)
            CD2_OFFSET(cFadeInOutInterface, m_pReplacing, 4)
            CD2_OFFSET(cFadeInOutInterface, m_pReplacedBy, 8)
            CD2_OFFSET(cFadeInOutInterface, m_nFadeStartTime, 0xC)
            CD2_OFFSET(cFadeInOutInterface, m_eFadeState, 0x10)
            CD2_OFFSET(cFadeInOutInterface, m_ePreviousFadeState, 0x14))
    };
}
#endif
