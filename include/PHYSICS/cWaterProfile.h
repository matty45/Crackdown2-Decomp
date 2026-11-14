#include "rws/attributes.h"
// PHYSICS::cWaterProfile (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x82697608) is slot 11 of the vtable at 0x82132DA0, as cNonGameBase's RetClassName.
// The debug-page inheritance registration survives in CD2, but its 0x7C allocation
// and factory's five interface stores leave no physical debug-page subobject.
#ifndef PHYSICS_CWATERPROFILE_H
#define PHYSICS_CWATERPROFILE_H

#include "gom/non_game_base.h"
#include "PHYSICS/cWaterCinfo.h"

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
        // CD2 deleting wrapper restores this class's interfaces, then calls cNonGameBase's destructor.
        virtual ~cWaterProfile() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
        static cWaterCinfo m_WaterInfo;
        enum LoadParameterTypes
        {
            CMD_WATER_LEVEL = 0, CMD_WAVE_AMPLITUDE, CMD_WAVE_FREQUENCY,
            CMD_WAVE_LENGTH, CMD_WAVE_GRADIENT, CMD_USING_BUOYANCY,
            CMD_WATER_LINEAR_DAMPING, CMD_WATER_ANGULAR_DAMPING,
            CMD_WATER_FWD_LINEAR_DAMPING, CMD_GROUND_LEVEL, CMD_MAX_HEIGHT_LEVEL
        };
    };
}

#endif // PHYSICS_CWATERPROFILE_H
