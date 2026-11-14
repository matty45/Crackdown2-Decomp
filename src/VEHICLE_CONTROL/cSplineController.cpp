// VEHICLE_CONTROL/cSplineController.cpp: RuffKing's Libraries/Shared/VehicleController/cSplineController.cpp.
// Its text range and the evidence for it are in config/splits.txt; its own functions are not written yet.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include <algorithm>

// CD2's range-fill helper takes float storage, an unsigned count and a value
// reference; the standard template retains a load from that reference each time.
template float *std::copy<float *, float *>(float *, float *, float *);
template float *std::copy_backward<float *, float *>(float *, float *, float *);
template void std::fill_n<float *, unsigned int, float>(float *, unsigned int, const float &);
