// CHARACTER::cCharacterController's header. The class itself is not modelled yet; this holds the header's static
// constants, which every object file that includes it copies. Names, namespace and order from the RuffKing PDB
// (shared/character/ccharactercontroller.h, initializers at lines 54-56; fDEG_TO_RAD is in the same objects in Burn).
// CD2 calls cos and tan with the angle as a double (45 and 50 times the float 0.017453, unrounded).
#ifndef CHARACTER_CCHARACTERCONTROLLER_H
#define CHARACTER_CCHARACTERCONTROLLER_H

#include <math.h>

namespace CHARACTER
{
    static const float fDEG_TO_RAD = 0.017453f;
    static const float fSlopeDotLimit = (float)cos(45.0 * fDEG_TO_RAD);
    static const float fStepDotLimit = (float)cos(50.0 * fDEG_TO_RAD);
    static const float fStepDotTan = (float)tan(50.0 * fDEG_TO_RAD);
}

#endif // CHARACTER_CCHARACTERCONTROLLER_H
