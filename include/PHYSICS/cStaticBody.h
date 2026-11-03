// STAND-IN: RuffKing cStaticBody derives from cBody. CD2 StaticCreateClass
// at 0x8268AE08 gives size 0x260; the final 0x10 bytes remain unmodelled.
#ifndef PHYSICS_CSTATICBODY_H
#define PHYSICS_CSTATICBODY_H
#include "PHYSICS/cBody.h"
namespace PHYSICS
{
    class cStaticBody : public cBody
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        unsigned char m_unmodelled250[0x10];
        CD2_LAYOUT_CHECKS(cStaticBody, CD2_SIZE(cStaticBody, 0x260))
    };
}
#endif
