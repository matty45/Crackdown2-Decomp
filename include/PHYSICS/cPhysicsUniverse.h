// PHYSICS::cPhysicsUniverse (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x8268DAE8) is slot 11 of the vtable at 0x82132A48, as cNonGameBase's RetClassName.
#ifndef PHYSICS_CPHYSICSUNIVERSE_H
#define PHYSICS_CPHYSICSUNIVERSE_H

#include "gom/non_game_base.h"

namespace PHYSICS
{
    class cPhysicsUniverse : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcPhysicsUniverseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PHYSICS_CPHYSICSUNIVERSE_H
