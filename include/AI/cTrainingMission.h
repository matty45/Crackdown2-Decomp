#ifndef AI_CTRAININGMISSION_H
#define AI_CTRAININGMISSION_H

#include "AI/cMission.h"
#include "rws/eventhandler.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    // RuffKing's bases. CD2's primary table (0x820075B8) starts with this class's RetClass and IsA and holds its RetClassName
    // in slot 17, as cMission's does.
    class cTrainingMission : public cMission, public RWS::CEventHandler
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8BBD0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cTrainingMissionClass = new Fun_Runtime::cClass(0xB4D6, "cTrainingMission", 0x9D0);
            return *cTrainingMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcTrainingMissionClass;

        cTrainingMission();
        // The body (0x82206500) lies in the order-list region; its deleting wrapper (0x8247F3F8) calls it.
        virtual ~cTrainingMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // RWS::CEventHandler's pure virtual (RuffKing declares the override).
        virtual void HandleEvents(RWS::CMsg &);
        // CD2: cTrainingMission's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Activate(); // cRegisteredClass 2: 0x82480900
        virtual void Deactivate(); // cRegisteredClass 3: 0x82480940
        virtual void TickUpdate(float); // cRegisteredClass 8: 0x82482E88
    protected:
        virtual void OnLeaveMissionState(unsigned char); // cRegisteredClass 29: 0x82482A30
        virtual void OnEnterMissionState(unsigned char); // cRegisteredClass 31: 0x82480E08
        virtual void OnLeaveGlobalMissionState(AI::cMission::etGlobalMissionState); // cRegisteredClass 32: 0x82480DF8
        virtual void OnMissionUnlocked(); // cRegisteredClass 35: 0x82480DA0
        virtual void GetSaveStateForMissionState(unsigned char &,unsigned char &); // cRegisteredClass 36: 0x82484C20
    };
}

#endif

