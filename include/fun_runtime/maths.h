// Fun_Runtime maths helpers: RuffKing's Fundamental/maths.h names and signatures (RuffKing keeps out-of-line copies,
// Clamp<float> at 0x822F45E0). The bodies are ours, from CD2's inlined copies: cTimeOfDay::SetPeriod (0x82774D98)
// tests the maximum first and returns the reference it selects.
#ifndef FUN_RUNTIME_MATHS_H
#define FUN_RUNTIME_MATHS_H
namespace Fun_Runtime
{
    template <class T>
    inline const T &Clamp(const T &val, const T &min, const T &max)
    {
        if (val > max)
            return max;
        if (val < min)
            return min;
        return val;
    }
}
#endif
