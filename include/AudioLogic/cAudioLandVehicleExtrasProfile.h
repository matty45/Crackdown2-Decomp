// AudioLogic::cAudioLandVehicleExtrasProfile (Crackdown 2): STAND-IN for the class name only. Base
// AudioLogic::cAudioBaseProfile, as in RuffKing's header; RetClassName (0x82527D98) is slot 11 of the vtable at
// 0x821114C0, as cNonGameBase's RetClassName.
#ifndef AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H
#define AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H

#include "AudioLogic/cAudioBaseProfile.h"
#include "fun_runtime/class.h"

namespace AudioLogic
{
    class cAudioLandVehicleExtrasProfile : public AudioLogic::cAudioBaseProfile
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioLandVehicleExtrasProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H
