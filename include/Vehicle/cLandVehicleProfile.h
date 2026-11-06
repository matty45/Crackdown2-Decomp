// Vehicle::cLandVehicleProfile: bases from RuffKing (cLandVehicleData, cRigidBodyProfile). The compiler places the
// polymorphic cRigidBodyProfile first; CD2's destructor (0x8269FA68) calls ~cRigidBodyProfile on the object and then
// cLandVehicleData's out-of-line destructor (0x8269DFE0) at 0x300. Size 0x8E0 (registrar), so cLandVehicleData is
// 0x5E0 bytes; its fields are not modelled.
#ifndef Vehicle_cLandVehicleProfile_H
#define Vehicle_cLandVehicleProfile_H

#include "PHYSICS/cRigidBodyProfile.h"
#include "cd2/layout.h"

namespace Vehicle
{
    // 16-byte aligned: RuffKing's cLandVehicleData holds Fun_Runtime::Vec3 members (m_HLPosOffset, m_DSSize, ...), and
    // CD2's derived profiles need it (cCarProfile: event at 0x8E0, size 0x8F0; cSixWheelerProfile: size 0x900).
    __declspec(align(16)) class cLandVehicleData
    {
    public:
        ~cLandVehicleData();

    private:
        unsigned char m_unmodelled[0x5E0];
    };

    class cLandVehicleProfile : public cLandVehicleData, public PHYSICS::cRigidBodyProfile
    {
    public:
        // CD2 0x8269F780: MakeNew (0x8269F730) calls it out of line with only this.
        cLandVehicleProfile();
        virtual ~cLandVehicleProfile();
        // CD2 0x8269FA58: attribute-handler vtable slot 6, returning Ret_OK.
        virtual Fun_Runtime::RetVal Term();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(cLandVehicleProfile, CD2_SIZE(cLandVehicleProfile, 0x8E0))
    };
}

#endif
