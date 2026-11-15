// cFrame (Crackdown 2): STAND-IN for the 8-byte frame reference (a clump and a node index). RuffKing declares it
// in the global namespace in GameRenderer/cLODClump.h; names and order from there. CD2's cLightAttachment keeps
// one at 0x18, between its owner (0x14) and its 16-byte-aligned transform (0x20).
#ifndef GAMERENDERER_CFRAME_H
#define GAMERENDERER_CFRAME_H

#include "cd2/layout.h"

namespace GameRenderer { class cLODClump; }

class cFrame
{
public:
    cFrame(GameRenderer::cLODClump *, unsigned char);
    cFrame();

private:
    GameRenderer::cLODClump *m_pLODClump;
    unsigned char m_nIndex;

    CD2_LAYOUT_CHECKS(cFrame,
        CD2_SIZE(cFrame, 0x8)
        CD2_OFFSET(cFrame, m_nIndex, 0x4))
};

#endif // GAMERENDERER_CFRAME_H
