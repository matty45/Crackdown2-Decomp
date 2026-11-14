// PHYSICS::cPickupProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8270CD10, from its registrars in CD2's
// initializer run); RuffKing names the class in cPickupProfile.obj. No layout or virtuals are modelled yet.
#ifndef PHYSICS_CPICKUPPROFILE_H
#define PHYSICS_CPICKUPPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace PHYSICS
{
    // RuffKing names CAttributeHandler as the primary base; CD2 0x8270CD10
    // constructs only its 0x18 bytes. The allocation-policy base has no retail state.
    class cPickupProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 table 0x82002EFC, slot 11.
        virtual const char *RetClassName() const;
        virtual void Destruct(); // CD2 primary slot 12, shared empty body.
        virtual ~cPickupProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
        // CD2 expands both static-array reset loops into its factory.
        cPickupProfile(const RWS::CAttributePacket &);
    protected:
        // Reference member names; CD2's factory resets 28 entries, rather
        // than the smaller effect/collision sets in RuffKing.
        static int m_aEffectID[28];
        struct tPickupCollisionData
        {
            float fRadiusOnFoot;
            float fHeightOnFoot;
            float fRadiusInVehicle;
        };
        static tPickupCollisionData ms_aPickupColData[28];
        CD2_LAYOUT_CHECKS(cPickupProfile, CD2_SIZE(cPickupProfile, 0x18))
    };
}

#endif // PHYSICS_CPICKUPPROFILE_H
