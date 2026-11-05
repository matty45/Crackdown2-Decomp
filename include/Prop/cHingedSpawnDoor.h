#include "rws/attributes.h"
// Prop::cHingedSpawnDoor (Crackdown 2): STAND-IN for the class name only. Base Prop::cHingedProp, as in RuffKing's
// header; RetClassName (0x82744A78) is slot 11 of the vtable at 0x82012810, as cNonGameBase's RetClassName.
#ifndef PROP_CHINGEDSPAWNDOOR_H
#define PROP_CHINGEDSPAWNDOOR_H

#include "Prop/cHingedProp.h"

namespace Prop
{
    class cHingedSpawnDoor : public Prop::cHingedProp
    {
    public:
        // CD2 0x82744AA8: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 placement factory 0x82744A88; constructor signature follows RuffKing.
        cHingedSpawnDoor(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcHingedSpawnDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CHINGEDSPAWNDOOR_H
