// STAND-IN: Burn's raw-animation/event/name record; CD2's map carries this value type.
#ifndef ANIM_CANIMDATA_H
#define ANIM_CANIMDATA_H
#include "Anim/cAnimEventSequence.h"
struct SAnimationCompressed;
namespace Anim
{
    class cAnimData
    {
    public:
        cAnimData();
        const SAnimationCompressed *m_pRawData;
        cAnimEventSequence m_Events;
        const char *m_sName;
        CD2_LAYOUT_CHECKS(cAnimData,
            CD2_SIZE(cAnimData, 0x10)
            CD2_OFFSET(cAnimData, m_pRawData, 0)
            CD2_OFFSET(cAnimData, m_Events, 4)
            CD2_OFFSET(cAnimData, m_sName, 0xC))
    };
}
#endif
