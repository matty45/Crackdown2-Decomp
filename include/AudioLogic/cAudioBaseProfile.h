// AudioLogic::cAudioBaseProfile: CD2 constructor 0x82527860 establishes the event
// and script interfaces at +0x18/+0x1C; descriptor size 0x60. Own member names
// come from RuffKing; CD2 adds the script base absent from that later build.
#ifndef AUDIOLOGIC_CAUDIOBASEPROFILE_H
#define AUDIOLOGIC_CAUDIOBASEPROFILE_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"
#include "fun_runtime/scripthost.h"
#include "fun_runtime/string.h"

namespace AudioEngine { class cEntity; }

namespace AudioLogic
{
    class cAudioBaseProfile : public RWS::CAttributeHandler, public RWS::CEventHandler,
        public Fun_Runtime::cScriptHost
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioBaseProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 primary table 0x82111430 ends with these reference-named slots.
        virtual void Destruct(); // slot 12
        virtual void ProcessEntity(AudioEngine::cEntity *); // slot 13
        virtual ~cAudioBaseProfile();
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Term();
        virtual void HandleEvents(RWS::CMsg &);
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
    public:
        // Out of line: CD2 0x82527860 (MakeNew calls it).
        cAudioBaseProfile();
        // CD2 0x82527B90 takes only the profile name; unlike RuffKing it has no this argument.
        static cAudioBaseProfile *GetAudioProfile(const char *profileName);

        bool m_bReset;
    protected:
        Fun_Runtime::cString m_sProfileName;
        RWS::CEventId m_Msg_Return_Audio_Self;

        CD2_LAYOUT_CHECKS(cAudioBaseProfile,
            CD2_SIZE(cAudioBaseProfile, 0x60)
            CD2_OFFSET(cAudioBaseProfile, m_bReset, 0x38)
            CD2_OFFSET(cAudioBaseProfile, m_sProfileName, 0x3C)
            CD2_OFFSET(cAudioBaseProfile, m_Msg_Return_Audio_Self, 0x58))

    };
}

#endif // AUDIOLOGIC_CAUDIOBASEPROFILE_H
