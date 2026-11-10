// Vehicle::cVehicleSeat (Crackdown 2): STAND-IN. Name and member names from RuffKing's Vehicle/cVehicleSeat.h
// (size 0x58, m_pOccupant at 0x30, m_pInteractor at 0x40). CD2's seats are 0x5C bytes (cVehicle's seat array,
// Vehicle/cVehicle.h) and its RetNumberOfOccupants (0x826D9208) / RetSeatsInUse (0x826D9278) read the two safe
// pointers' payloads at 0x40 and 0x50, so CD2 has four more bytes before them. Only the two safe pointers are modelled.
#ifndef VEHICLE_CVEHICLESEAT_H
#define VEHICLE_CVEHICLESEAT_H

#include "cd2/layout.h"
#include "fun_runtime/safedeletablepointer.h"
#include "CHARACTER/cCharacter.h"

namespace Vehicle
{
    class cVehicleSeat
    {
    public:
        // Inlined by CD2 into cVehicle's occupancy queries.
        CHARACTER::cCharacter *RetOccupant() { return m_pOccupant; }
        CHARACTER::cCharacter *RetInteractor() { return m_pInteractor; }

    protected:
        unsigned char m_unmodelled0[0x34];
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pOccupant;      // 0x34
        Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pInteractor;    // 0x44
        unsigned char m_unmodelled54[0x5C - 0x54];

        CD2_LAYOUT_CHECKS(cVehicleSeat,
            CD2_SIZE(cVehicleSeat, 0x5C)
            CD2_OFFSET(cVehicleSeat, m_pOccupant, 0x34)
            CD2_OFFSET(cVehicleSeat, m_pInteractor, 0x44))
    };
}

#endif // VEHICLE_CVEHICLESEAT_H
