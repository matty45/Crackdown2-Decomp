// Fun_Runtime::OldVec3: the three-float vector (x, y, z and a pad word; RuffKing's layout and name). Evidence for
// ZeroVec's type: CD2 reads the zero vector at 0x8383A850 only as three floats (+0, +4, +8, over 200 times each,
// never +0xC and never as a __vector4), and its initializer (0x82FD5C3C) stores three floats. RuffKing's ZeroVec is a
// Vec3 and is what its AI::cPedestrianBase constructor reads where CD2's reads 0x8383A850.
// Later controller recovery adds evidence missing from the observation above: ZeroLastControlsVelocity
// (0x8255E510 and 0x82564688) loads the complete 16-byte zero object. Its three-float initializer
// and the existing OldVec3 conversions still match; resolving the global's original type remains open.
#ifndef FUN_RUNTIME_OLDVEC3_H
#define FUN_RUNTIME_OLDVEC3_H

namespace Fun_Runtime
{
    class OldVec3
    {
    public:
        float x;
        float y;
        float z;
        unsigned int pad;
    };

    extern const OldVec3 ZeroVec;
    // RuffKing's constants.cpp defines the axes after ZeroVec, 16 bytes apart. CD2's initializers 0x82FD5C50,
    // 0x82FD5C78 and 0x82FD5CA0 store (1,0,0), (0,1,0) and (0,0,1) as three floats at 0x8383A860/70/80, and
    // cChainGunPrototype's constructor (0x82616EB0) reads XAxis's three floats into a Vec3 (w = 1).
    extern const OldVec3 XAxis;
    extern const OldVec3 YAxis;
    extern const OldVec3 ZAxis;
}

#endif // FUN_RUNTIME_OLDVEC3_H
