#include "cd2/layout.h"
#include "rws/attributes.h"
// PHYSICS::cPhysicsUniverse (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x8268DAE8) is slot 11 of the vtable at 0x82132A48, as cNonGameBase's RetClassName.
// Known wrong, left for a structural fix: CD2 also registers it under GDb::cDebugPageHandler (inheritance registrar 0x82FE1340), RuffKing's second base. The
// stand-in lacks that base, so everything after its first base is not laid out as in CD2.
#ifndef PHYSICS_CPHYSICSUNIVERSE_H
#define PHYSICS_CPHYSICSUNIVERSE_H

#include "gom/non_game_base.h"

class hkAabbPhantom;

namespace PHYSICS
{
    class cBody;
    class cPhysicsWorld;
    class cPhysicsUniverse : public cNonGameBase
    {
    public:
        // RuffKing's callback interface (one pure slot, 4 bytes); CD2's cPulse table 0x821217D4 starts with it.
        class cFindBodiesCallback
        {
        public:
            virtual void BodyFoundCallback(cBody *) = 0;
        };
        // RuffKing's name and signature; CD2 0x821DA1E8, called by cPulse::Update (0x8260F378).
        static void FindBodiesInAabb(hkAabbPhantom *pPhantom, cFindBodiesCallback &CB);
        // RuffKing static name; CD2 RemoveWedge (0x826CC448) loads it at 0x83800DD4.
        static cPhysicsWorld *m_pPrimaryWorld;
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
