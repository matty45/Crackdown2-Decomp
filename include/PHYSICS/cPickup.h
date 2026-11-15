// STAND-IN: RuffKing declares cPickup as a field-less cPickupBase derivative.
// CD2 descriptor 0x8270A4D8 confirms its complete size is 0x150.
// Its virtual overrides are not recovered here yet.
#ifndef PHYSICS_CPICKUP_H
#define PHYSICS_CPICKUP_H
#include "PHYSICS/cPickupBase.h"
namespace PHYSICS
{
    class cPickup : public cPickupBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPickupClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
        CD2_LAYOUT_CHECKS(cPickup, CD2_SIZE(cPickup, 0x150))
    };
}
#endif
