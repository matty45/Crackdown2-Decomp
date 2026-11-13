#include "rws/attributes.h"
// AudioLogic::cAudioLandVehicleExtrasProfile (Crackdown 2): STAND-IN for the class name only. Base
// AudioLogic::cAudioBaseProfile, as in RuffKing's header; RetClassName (0x82527D98) is slot 11 of the vtable at
// 0x821114C0, as cNonGameBase's RetClassName.
#ifndef AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H
#define AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H

#include "AudioLogic/cAudioBaseProfile.h"
#include "fun_runtime/class.h"
#include "AudioEngine/cAudioGraph.h"

namespace AudioLogic
{
    class cAudioLandVehicleExtrasProfile : public AudioLogic::cAudioBaseProfile
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioLandVehicleExtrasProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x82527CF8 inlines the five graph constructors after base construction.
        __forceinline cAudioLandVehicleExtrasProfile() {}
        virtual ~cAudioLandVehicleExtrasProfile() {}
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Term();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        enum LoadParameterTypes
        {
            CMD_TAKEOFF_RPM_VS_TIME = 0, CMD_DISENGAGE_RPM_VS_TIME,
            CMD_ENGAGE_RPM_VS_TIME, CMD_DISENGAGE_LOAD_VS_TIME, CMD_ENGAGE_LOAD_VS_TIME
        };

        AudioEngine::cAudioGraph m_TakeoffRPMVsTime;
        AudioEngine::cAudioGraph m_GearDisengageRPMVsTime;
        AudioEngine::cAudioGraph m_GearEngageRPMVsTime;
        AudioEngine::cAudioGraph m_GearDisengageLoadVsTime;
        AudioEngine::cAudioGraph m_GearEngageLoadVsTime;

        CD2_LAYOUT_CHECKS(cAudioLandVehicleExtrasProfile,
            CD2_SIZE(cAudioLandVehicleExtrasProfile, 0x18C)
            CD2_OFFSET(cAudioLandVehicleExtrasProfile, m_TakeoffRPMVsTime, 0x60)
            CD2_OFFSET(cAudioLandVehicleExtrasProfile, m_GearDisengageRPMVsTime, 0x9C)
            CD2_OFFSET(cAudioLandVehicleExtrasProfile, m_GearEngageRPMVsTime, 0xD8)
            CD2_OFFSET(cAudioLandVehicleExtrasProfile, m_GearDisengageLoadVsTime, 0x114)
            CD2_OFFSET(cAudioLandVehicleExtrasProfile, m_GearEngageLoadVsTime, 0x150))
    };
}

#endif // AUDIOLOGIC_CAUDIOLANDVEHICLEEXTRASPROFILE_H
