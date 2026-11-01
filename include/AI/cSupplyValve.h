// AI::cSupplyValve (Crackdown 2): STAND-IN for the class name only. Base Prop::cSpinningProp, as in RuffKing's header;
// RetClassName (0x82457C10) is slot 11 of the vtable at 0x82102438, as cNonGameBase's RetClassName.
#ifndef AI_CSUPPLYVALVE_H
#define AI_CSUPPLYVALVE_H

#include "Prop/cSpinningProp.h"

namespace AI
{
    class cSupplyValve : public Prop::cSpinningProp
    {
    public:
        static const Fun_Runtime::cClass *ms_pcSupplyValveClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CSUPPLYVALVE_H
