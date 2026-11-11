// Havok's primary object interface; reference layout is one vptr (4 bytes).
#ifndef HAVOK_HKBASEOBJECT_H
#define HAVOK_HKBASEOBJECT_H
#include "cd2/layout.h"
class hkBaseObject
{
public:
    virtual ~hkBaseObject();
    CD2_LAYOUT_CHECKS(hkBaseObject, CD2_SIZE(hkBaseObject, 4))
};
#endif
