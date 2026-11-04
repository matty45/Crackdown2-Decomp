#include "cd2/layout.h"
#include "rws/attributes.h"
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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcPhysicsUniverseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8268E2D0 (MakeNew calls it).
        cPhysicsUniverse();

    private:
        unsigned char m_unmodelled7C[0x80 - 0x7C];

        CD2_LAYOUT_CHECKS(cPhysicsUniverse, CD2_SIZE(cPhysicsUniverse, 0x80))

    };
}

#endif // PHYSICS_CPHYSICSUNIVERSE_H
