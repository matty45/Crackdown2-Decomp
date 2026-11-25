#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Prop::cTODSlidingDoor (Crackdown 2): STAND-IN for the class name only. Base Prop::cSlidingDoor, as in RuffKing's
// header; RetClassName (0x82746F70) is slot 11 of the vtable at 0x82012230, as cNonGameBase's RetClassName.
#ifndef PROP_CTODSLIDINGDOOR_H
#define PROP_CTODSLIDINGDOOR_H

#include "Prop/cSlidingDoor.h"

namespace Prop
{
    class cTODSlidingDoor : public Prop::cSlidingDoor
    {
    public:
        // Inlined into the placement factory (0x82746F80), which calls cSlidingDoor's constructor (0x82746A78) with the
        // prototype and installs this class's tables: no fields of its own. __forceinline: without it the factory calls
        // the constructor (docs/matching-notes.md, "Inlining").
        __forceinline cTODSlidingDoor(GOM::cObjectPrototype *pPrototype) : cSlidingDoor(pPrototype) {}
        // CD2 spawning initializer 0x82FFC0C8 names placement factory 0x82746f80.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTODSlidingDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x82746EC8 (the start of this object's code) and 0x8220B0E0 (order-list region): the registered-class pair.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // CD2 table 0x82012230 (stored by the factory) differs from cSlidingDoor's at these slots; RuffKing's
        // cTODSlidingDoor overrides all three.
        virtual void TickUpdate(float dt); // 23: 0x82210C50
        virtual bool NeedsEnvironmentCollision(); // 171: 0x827E56A8 (the shared "return false" body)
        virtual void GoToInitialState(); // 363: 0x827472A8
    };
}

#endif // PROP_CTODSLIDINGDOOR_H
