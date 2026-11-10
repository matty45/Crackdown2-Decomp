// STAND-IN: shared 16-byte quaternion storage. The ambient-spawner and spawn-point
// reference layouts place Quat on a 16-byte boundary and reserve four floats.
#ifndef FUN_RUNTIME_QUAT_H
#define FUN_RUNTIME_QUAT_H

namespace Fun_Runtime
{
    // Stand-ins: RuffKing names, layouts as used here.
    __declspec(align(16)) struct Quat { float v[4]; };
}

#endif
