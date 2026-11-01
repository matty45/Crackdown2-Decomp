// Prop::cTurretBase (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82747FD8) is slot 11 of the vtable at 0x82144C88, as cNonGameBase's RetClassName.
#ifndef PROP_CTURRETBASE_H
#define PROP_CTURRETBASE_H

#include "Prop/cProp.h"

namespace Prop
{
    class cTurretBase : public Prop::cProp
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcTurretBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CTURRETBASE_H
