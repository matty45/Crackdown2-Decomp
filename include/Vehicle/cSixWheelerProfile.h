// Vehicle::cSixWheelerProfile: base and m_Msg_Data_Modified from RuffKing. CD2's destructor unregisters the event at 0x8F4
// before cLandVehicleProfile's destructor. Size 0x900 (registrar).
#ifndef Vehicle_cSixWheelerProfile_H
#define Vehicle_cSixWheelerProfile_H

#include "Vehicle/cLandVehicleProfile.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace Vehicle
{
    class cSixWheelerProfile : public cLandVehicleProfile
    {
    public:
        virtual ~cSixWheelerProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // RuffKing's tCollisionRamp (five floats); not modelled.
        unsigned char m_CollisionRamp[0x14];        // 0x8E0
        RWS::CEventId m_Msg_Data_Modified;           // 0x8F4

        CD2_LAYOUT_CHECKS(cSixWheelerProfile,
            CD2_SIZE(cSixWheelerProfile, 0x900)
            CD2_OFFSET(cSixWheelerProfile, m_Msg_Data_Modified, 0x8F4))
    };
}

#endif
