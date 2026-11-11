// Reference Havok broad-phase handle storage.
#ifndef HAVOK_HKBROADPHASEHANDLE_H
#define HAVOK_HKBROADPHASEHANDLE_H
#include "cd2/layout.h"
class hkBroadPhaseHandle
{
public:
    unsigned int m_id;
    CD2_LAYOUT_CHECKS(hkBroadPhaseHandle, CD2_SIZE(hkBroadPhaseHandle, 4))
};
#endif
