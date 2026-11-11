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
        // CD2 primary data-table slot 3 differs from cLandVehicleProfile.
        virtual void SetupMultiAxles();

        virtual ~cSixWheelerProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // RuffKing's tCollisionRamp (five floats); not modelled.
        unsigned char m_CollisionRamp[0x14];        // 0x8E0
        RWS::CEventId m_Msg_Data_Modified;           // 0x8F4

        // CD2: cSixWheelerProfile's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x826A5240
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x826A50F8
        virtual Fun_Runtime::RetVal Term(); // 6: 0x826A5168
    private:
        CD2_LAYOUT_CHECKS(cSixWheelerProfile,
            CD2_SIZE(cSixWheelerProfile, 0x900)
            CD2_OFFSET(cSixWheelerProfile, m_Msg_Data_Modified, 0x8F4))
    };
}

#endif
