// AudioLogic::cAudioLandVehicleProfile (Crackdown 2): STAND-IN for the class name only. Base
// AudioLogic::cAudioBaseProfile, as in RuffKing's header; RetClassName (0x825280D8) is slot 11 of the vtable at
// 0x8211154C, as cNonGameBase's RetClassName.
#ifndef AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H
#define AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H

#include "AudioLogic/cAudioBaseProfile.h"
#include "fun_runtime/class.h"

namespace AudioLogic
{
    class cAudioLandVehicleProfile : public AudioLogic::cAudioBaseProfile
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioLandVehicleProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H
