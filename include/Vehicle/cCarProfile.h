// Vehicle::cCarProfile: base and m_Msg_Data_Modified from RuffKing. CD2's destructor unregisters the event at 0x8E0
// before cLandVehicleProfile's destructor. Size 0x8F0 (registrar).
#ifndef Vehicle_cCarProfile_H
#define Vehicle_cCarProfile_H

#include "Vehicle/cLandVehicleProfile.h"
#include "rws/eventid.h"
#include "cd2/layout.h"

namespace Vehicle
{
    class cCarProfile : public cLandVehicleProfile
    {
    public:
        virtual ~cCarProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        RWS::CEventId m_Msg_Data_Modified;           // 0x8E0

        CD2_LAYOUT_CHECKS(cCarProfile,
            CD2_SIZE(cCarProfile, 0x8F0)
            CD2_OFFSET(cCarProfile, m_Msg_Data_Modified, 0x8E0))
    };
}

#endif
