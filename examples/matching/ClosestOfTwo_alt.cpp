// Crackdown 2 (Xbox 360, title update build) - byte-exact match
// Target : 0x82401C88, 128 bytes
// Author : Haiku 5.5 (agent pilot P5), 1 harness run
// Notes  : Independent second solution of the same function, written differently: two different sources can compile to identical bytes.
// Types below are minimal stand-ins written for this one function, not real headers.
// Verify : py -I verify.py <path to extracted default.exe>

float* PickClosest(float* a1, float* a2, float* a3)
{
    if (a2 == 0)
        return a3;
    if (a3 == 0)
        return a2;

    float dy2 = a1[1] - a2[2];
    float dy3 = a1[1] - a3[2];
    float dz2 = a1[2] - a2[3];
    float dz3 = a1[2] - a3[3];
    float dx2 = a1[0] - a2[1];
    float dx3 = a1[0] - a3[1];

    float d2 = dx2 * dx2 + (dz2 * dz2 + dy2 * dy2);
    float d3 = dx3 * dx3 + (dz3 * dz3 + dy3 * dy3);
    if (d2 < d3)
        return a2;
    return a3;
}

