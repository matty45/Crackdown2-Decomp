// PHYSICS::cPickupProfile (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8270CD10, from its registrars in CD2's
// initializer run); RuffKing names the class in cPickupProfile.obj. No layout or virtuals are modelled yet.
#ifndef PHYSICS_CPICKUPPROFILE_H
#define PHYSICS_CPICKUPPROFILE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace PHYSICS
{
    class cPickupProfile
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // PHYSICS_CPICKUPPROFILE_H
