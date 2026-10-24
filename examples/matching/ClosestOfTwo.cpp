// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x82401C88, 128 bytes
// Author : Sonnet 5.5 (agent pilot P5), 4 harness runs
// Notes  : Cold function (no reference): returns the nearer of two objects to a position. Exercises /fp:fast (fmadds).
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

struct Obj { float pad; float x, y, z; };
static inline float DistSq(const float* p, const Obj* o) {
    float dy = p[1] - o->y;
    float dz = p[2] - o->z;
    float dx = p[0] - o->x;
    return dx * dx + (dz * dz + dy * dy);
}
const Obj* Closest(const float* pos, const Obj* a, const Obj* b) {
    if (!a) return b;
    if (!b) return a;
    float da = DistSq(pos, a);
    float db = DistSq(pos, b);
    if (da < db)
        return a;
    return b;
}

