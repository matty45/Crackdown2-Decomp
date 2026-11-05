// POD stand-in; type and field names are ours. CD2's render-to-texture vector
// insert routine (0x827A9F38) copies eight-byte values. The manager initializes
// both words of each of five entries to zero; their meanings are unrecovered.
#ifndef UNKNOWN_CRENDERTOTEXTUREENTRY_H
#define UNKNOWN_CRENDERTOTEXTUREENTRY_H
#include "cd2/layout.h"
namespace unknown
{
    struct cRenderToTextureEntry
    {
        unsigned int m_word0;
        unsigned int m_word4;
        CD2_LAYOUT_CHECKS(cRenderToTextureEntry,
            CD2_SIZE(cRenderToTextureEntry, 8)
            CD2_OFFSET(cRenderToTextureEntry, m_word0, 0)
            CD2_OFFSET(cRenderToTextureEntry, m_word4, 4))
    };
}
#endif
