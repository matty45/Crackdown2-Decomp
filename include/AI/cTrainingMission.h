#ifndef AI_CTRAININGMISSION_H
#define AI_CTRAININGMISSION_H

#include "AI/cMission.h"
#include "rws/eventhandler.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"
#include "GMan/cGameManager.h"

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
        // CD2 0x8247F038; the linker folded cFinalMission's and cBeaconMission's identical bodies into it.
        virtual void Destruct();

        // RuffKing's mission states.
        enum eTrainingMissionState
        {
            eTMS_InitialRespawn = 0,
            eTMS_WaitOnTrigger,
            eTMS_TrainingIntro,
            eTMS_SystemCheckIntro,
            eTMS_SystemCheckHealth,
            eTMS_SystemCheckMiniMap,
            eTMS_SystemCheckReticule,
            eTMS_SystemCheckAimIntro,
            eTMS_SystemCheckAim,
            eTMS_SystemInvertOption,
            eTMS_SystemCheckOutro,
            eTMS_AgilityIntro,
            eTMS_AgilityOrbOutro,
            eTMS_AgilityRaceIntro,
            eTMS_AgilityRace,
            eTMS_AgilityRaceFail,
            eTMS_AgilityRaceOutro,
            eTMS_LeapOfFaith,
            eTMS_LeapOfFaithOutro,
            eTMS_FirearmsPickupRifle,
            eTMS_FirearmsFreeAimIntro,
            eTMS_FirearmsFreeAim,
            eTMS_FirearmsSubTarget,
            eTMS_FirearmsPickupShotgun,
            eTMS_FirearmsSurvivalIntro,
            eTMS_FirearmsSurvival,
            eTMS_StrengthIntro,
            eTMS_StrengthPracticeIntro,
            eTMS_StrengthPractice,
            eTMS_StrengthSurvivalIntro,
            eTMS_StrengthSurvival,
            eTMS_ExplosivesPickupGrenade,
            eTMS_ExplosivesIntro,
            eTMS_Explosives,
            eTMS_DrivingIntro,
            eTMS_DrivingComplete,
            eTMS_AwaitingPickup,
            eTMS_Finale,
            eTMS_Complete,
            eTMS_Num,
        };

        void StopMission();                             // CD2 0x82480978
        // RuffKing's name; CD2 expands it into OnMissionUnlocked (0x82480DA0).
        void StartMission()
        {
            StopMission();
            SetMissionState(eTMS_InitialRespawn, true);
            LinkMsg(iMsgRestartPlayer, "Mtx *", 0x8000);
        }
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

    private:
        // Size 0x9D0 from CD2's registrar and MakeNew (0x8247EFE8); the fields after the event handler at 0x3C0 are
        // not modelled.
        unsigned char m_unmodelled3C4[0x9D0 - 0x3C4];
        CD2_LAYOUT_CHECKS(cTrainingMission, CD2_SIZE(cTrainingMission, 0x9D0))
    };
}

#endif

