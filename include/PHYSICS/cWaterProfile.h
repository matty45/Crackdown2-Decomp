#include "rws/attributes.h"
// PHYSICS::cWaterProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x82697608) is slot 11 of the vtable at 0x82132DA0, as cNonGameBase's RetClassName.
// Known wrong, left for a structural fix: CD2 also registers it under GDb::cDebugPageHandler (inheritance registrar 0x82FE26D8), RuffKing's second base. The
// stand-in lacks that base, so everything after its first base is not laid out as in CD2.
#ifndef PHYSICS_CWATERPROFILE_H
#define PHYSICS_CWATERPROFILE_H

#include "gom/non_game_base.h"

namespace PHYSICS
{
    class cWaterProfile : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcWaterProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // PHYSICS_CWATERPROFILE_H
