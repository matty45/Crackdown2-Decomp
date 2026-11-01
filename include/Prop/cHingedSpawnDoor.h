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
        static const Fun_Runtime::cClass *ms_pcHingedSpawnDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CHINGEDSPAWNDOOR_H
