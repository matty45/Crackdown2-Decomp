// cVehicleControls (Crackdown 2): STAND-IN. Name from RuffKing (Physics/physicsconsts.h, global namespace), where it is
// 0x20 bytes: six floats, four bools and a byte of flags. CD2's is 0x18 bytes: cVehicle's constructor (0x826CCD70)
// stores a float constant at +0, +4 and +8 of the copy at 0xCCC and bytes at +0xC..+0x17, and cVehicle::HandleEvents
// (0x826CE3F0) copies the message's controls as six words. Only RuffKing's first three floats are named; the bytes after
// them are not modelled yet.
#ifndef PHYSICS_CVEHICLECONTROLS_H
#define PHYSICS_CVEHICLECONTROLS_H

#include "cd2/layout.h"

class cVehicleControls
{
public:
    float m_fSteering;
    float m_fAccelerator;
    float m_fBrake;
private:
    unsigned char m_unmodelledC[0x18 - 0xC];

    CD2_LAYOUT_CHECKS(cVehicleControls,
        CD2_SIZE(cVehicleControls, 0x18)
        CD2_OFFSET(cVehicleControls, m_fBrake, 8))
};

#endif // PHYSICS_CVEHICLECONTROLS_H
