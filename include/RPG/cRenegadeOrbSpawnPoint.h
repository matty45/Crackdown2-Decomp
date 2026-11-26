// RPG::cRenegadeOrbSpawnPoint (Crackdown 2): StaticCreateClass 0x827588A8, MakeNew 0x82758940, from its registrars in
// CD2's initializer run; RuffKing names the class in cRenegadeOrbSpawnPoint.obj. Base Activity::cSpawnPointBase from
// CD2's inheritance registrar. MakeNew expands the constructor: its stores give RuffKing's fields (RuffKing's 0x90..0xC8)
// at CD2's 0x50..0x88, after CD2's 0x50-byte base, and the class's one table, 0x82145EA0 (13 slots).
#ifndef RPG_CRENEGADEORBSPAWNPOINT_H
#define RPG_CRENEGADEORBSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"
#include "cd2/layout.h"

namespace AI { class cPatrolRoute; }
namespace SaveGame { class cLoadStream; class cSaveStream; }

namespace RPG
{
    class cRenegadeOrbSpawnPoint : public Activity::cSpawnPointBase
    {
    public:
        // CD2 0x82758838 / 0x82758848: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbSpawnPointClass;

        // Expanded in MakeNew (0x82758940). CD2's table holds the deleting destructor 0x823D01B8, which another spawn
        // point's table shares: no destructor is declared (an empty one would store this class's table first).
        // __forceinline: /Ob1 declines a constructor this size; CD2's MakeNew expands it.
        __forceinline cRenegadeOrbSpawnPoint()
            : m_pCircuit(0), m_fMaxVelocity(0.0f), m_fAcceleration(0.0f), m_fDeceleration(0.0f),
              m_fChangeDirectionTime(0.0f), m_fSwitchDirectionDeceleration(0.0f), m_fActivationRadiusSq(0.0f),
              m_bAvoidPlayer(true), m_bSmoothMovement(true), m_bSmoothMovementConstantVelocity(true),
              m_fHoverMagnitudeX(0.0f), m_fHoverMagnitudeY(0.0f), m_fHoverTimerModX(0.0f), m_fHoverTimerModY(0.0f),
              m_nNumSkillPickups(0), m_fSkillBonus(0.0f)
        {
        }

        // CD2 table 0x82145EA0 differs from cSpawnPointBase's at these slots; names and order are RuffKing's.
        virtual void SetInAV(Activity::cActivityVolume *pAV, bool bInside); // 3: 0x827591D0
        virtual cNonGameBase *Spawn(); // 6: 0x827590A8
        virtual void HandleAttributes(const RWS::CAttributePacket &attr); // 9: 0x82758A40
        virtual void Load(SaveGame::cLoadStream *pStream); // 11: 0x827592A8
        virtual void Save(SaveGame::cSaveStream *pStream); // 12: 0x82759340

    private:
        const AI::cPatrolRoute *m_pCircuit;
        float m_fMaxVelocity;
        float m_fAcceleration;
        float m_fDeceleration;
        float m_fChangeDirectionTime;
        float m_fSwitchDirectionDeceleration;
        float m_fActivationRadiusSq;
        bool m_bAvoidPlayer;
        bool m_bSmoothMovement;
        bool m_bSmoothMovementConstantVelocity;
        float m_fHoverMagnitudeX;
        float m_fHoverMagnitudeY;
        float m_fHoverTimerModX;
        float m_fHoverTimerModY;
        unsigned char m_nNumSkillPickups;
        float m_fSkillBonus;
        // RuffKing's PHYSICS::eArea m_eArea (the constructor leaves it).
        unsigned char m_unmodelled88[0x90 - 0x88];

        CD2_LAYOUT_CHECKS(cRenegadeOrbSpawnPoint,
            CD2_SIZE(cRenegadeOrbSpawnPoint, 0x90)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_pCircuit, 0x50)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_fActivationRadiusSq, 0x68)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_bAvoidPlayer, 0x6C)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_fHoverMagnitudeX, 0x70)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_nNumSkillPickups, 0x80)
            CD2_OFFSET(cRenegadeOrbSpawnPoint, m_fSkillBonus, 0x84))
    };
}

#endif // RPG_CRENEGADEORBSPAWNPOINT_H
