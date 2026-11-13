#include "rws/attributes.h"
// AudioLogic::cAudioLandVehicleProfile (Crackdown 2): STAND-IN for the class name only. Base
// AudioLogic::cAudioBaseProfile, as in RuffKing's header; RetClassName (0x825280D8) is slot 11 of the vtable at
// 0x8211154C, as cNonGameBase's RetClassName.
#ifndef AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H
#define AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H

#include "AudioLogic/cAudioBaseProfile.h"
#include "fun_runtime/class.h"

namespace AudioLogic
{
    class cAudioLandVehicleExtrasProfile;
    class cAudioLandVehicleProfile : public AudioLogic::cAudioBaseProfile
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioLandVehicleProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 factory 0x82528050 calls the base constructor, then installs these tables.
        __forceinline cAudioLandVehicleProfile() {}
        virtual ~cAudioLandVehicleProfile() {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Term();
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        // RuffKing names/order; CD2's complete size is 0x7C after the 0x60 base.
        cAudioLandVehicleExtrasProfile *m_pExtrasProfile;
        float m_fFakeRevPeakRPM;
        float m_fFakeRevStartDelay;
        float m_fFakeRevRampUp;
        float m_fFakeRevRampDown;
        float m_fAudioRPMMin;
        float m_fAudioRPMMax;

        CD2_LAYOUT_CHECKS(cAudioLandVehicleProfile,
            CD2_SIZE(cAudioLandVehicleProfile, 0x7C)
            CD2_OFFSET(cAudioLandVehicleProfile, m_pExtrasProfile, 0x60)
            CD2_OFFSET(cAudioLandVehicleProfile, m_fFakeRevPeakRPM, 0x64)
            CD2_OFFSET(cAudioLandVehicleProfile, m_fAudioRPMMax, 0x78))
    };
}

#endif // AUDIOLOGIC_CAUDIOLANDVEHICLEPROFILE_H
