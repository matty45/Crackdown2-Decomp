// Fun_Runtime::OldVec3: the three-float vector (x, y, z and a pad word; RuffKing's layout and name). Evidence for
// ZeroVec's type: CD2 reads the zero vector at 0x8383A850 only as three floats (+0, +4, +8, over 200 times each,
// never +0xC and never as a __vector4), and its initializer (0x82FD5C3C) stores three floats. RuffKing's ZeroVec is a
// Vec3 and is what its AI::cPedestrianBase constructor reads where CD2's reads 0x8383A850.
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
}

#endif // FUN_RUNTIME_OLDVEC3_H
