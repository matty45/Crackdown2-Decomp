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
    };
}

#endif // PHYSICS_CPICKUPPROFILE_H
