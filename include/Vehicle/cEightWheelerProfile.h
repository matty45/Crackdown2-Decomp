// Vehicle::cEightWheelerProfile: base and m_Msg_Data_Modified from RuffKing. CD2's destructor unregisters the event at 0x8E0
// before cLandVehicleProfile's destructor. Size 0x8F0 (registrar).
#ifndef Vehicle_cEightWheelerProfile_H
#define Vehicle_cEightWheelerProfile_H

#include "Vehicle/cLandVehicleProfile.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace Vehicle
{
    class cEightWheelerProfile : public cLandVehicleProfile
    {
    public:
        virtual ~cEightWheelerProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        RWS::CEventId m_Msg_Data_Modified;           // 0x8E0

        CD2_LAYOUT_CHECKS(cEightWheelerProfile,
            CD2_SIZE(cEightWheelerProfile, 0x8F0)
            CD2_OFFSET(cEightWheelerProfile, m_Msg_Data_Modified, 0x8E0))
    };
}

#endif
