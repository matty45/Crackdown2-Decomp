// Vehicle::cGenVehicleProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x8269C6C0) is slot 11 of the vtable at 0x821332D0, as cNonGameBase's RetClassName.
#ifndef VEHICLE_CGENVEHICLEPROFILE_H
#define VEHICLE_CGENVEHICLEPROFILE_H

#include "gom/non_game_base.h"

namespace Vehicle
{
    class cGenVehicleProfile : public cNonGameBase
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif // VEHICLE_CGENVEHICLEPROFILE_H
