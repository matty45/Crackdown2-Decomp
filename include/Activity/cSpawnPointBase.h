// Activity::cSpawnPointBase (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D2A98, from its registrars in CD2's
// initializer run); RuffKing names the class in cSpawnPointBase.obj. No layout or virtuals are modelled yet.
// Reconstruction update: the shared base layout and CD2 virtual interface are now modelled below.
#ifndef ACTIVITY_CSPAWNPOINTBASE_H
#define ACTIVITY_CSPAWNPOINTBASE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/quat.h"

class cNonGameBase;
namespace GOM { class cObjectPrototype; }
namespace AI { class Squad; }
namespace Fun_Runtime { class Mtx; }

namespace Activity
{
    class cActivityVolume;
    // Burn's release base has no ActionIO interface. CD2's cSpawnPoint constructor
    // (0x823D1F80) agrees with its position, rotation, prototype and state offsets.
    // The concrete tables at 0x82002810 and 0x82155260 have eleven slots.
    class cSpawnPointBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSpawnPointBaseClass;
        // Burn names the UID counter. CD2 0x823D1F80 initializes the shared
        // base inline and increments its data word at 0x830AC820 (initially 1000).
        static unsigned int ms_nNextUID;
        cSpawnPointBase();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cSpawnPointBase();
        virtual void SetInAV(cActivityVolume *, bool);
        virtual unsigned int RetSpawnedObjectID() const;
        virtual bool IsLocallyBlocked() const;
        virtual cNonGameBase *Spawn() = 0;
        virtual AI::Squad *InitSquadProxyForEntity(unsigned int, unsigned char, unsigned int);
        virtual bool IsSignificantOnMinimap() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // Burn names SetTransform; CD2 0x823D2840 stores position and derives
        // the quaternion from the supplied matrix. HandleSystemCommands calls it.
        void SetTransform(const Fun_Runtime::Mtx &);

    protected:
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);
        Fun_Runtime::Vec3 m_Pos;
        Fun_Runtime::Quat m_Rot;
        GOM::cObjectPrototype *m_pPrototype;
        cNonGameBase *m_pSpawned;

    private:
        unsigned int m_nAVBitfield;
        unsigned char m_nAVRefCount;
        // Names ours: SetInAV (0x823D2C98) records local-volume membership at
        // +0x3D; IsLocallyBlocked (0x823D0188) bypasses that check when +0x3E is true.
        bool m_bInLocalAV;
        bool m_bIgnoreLocalBlocking;
        unsigned int m_nARSquadID;
        unsigned int m_nUID;
        unsigned char m_nStatusBitfield;
        bool m_bPersistingObject;

        CD2_LAYOUT_CHECKS(cSpawnPointBase,
            CD2_SIZE(cSpawnPointBase, 0x50)
            CD2_OFFSET(cSpawnPointBase, m_Pos, 0x10)
            CD2_OFFSET(cSpawnPointBase, m_Rot, 0x20)
            CD2_OFFSET(cSpawnPointBase, m_pPrototype, 0x30)
            CD2_OFFSET(cSpawnPointBase, m_pSpawned, 0x34)
            CD2_OFFSET(cSpawnPointBase, m_nAVBitfield, 0x38)
            CD2_OFFSET(cSpawnPointBase, m_nAVRefCount, 0x3C)
            CD2_OFFSET(cSpawnPointBase, m_bInLocalAV, 0x3D)
            CD2_OFFSET(cSpawnPointBase, m_bIgnoreLocalBlocking, 0x3E)
            CD2_OFFSET(cSpawnPointBase, m_nARSquadID, 0x40)
            CD2_OFFSET(cSpawnPointBase, m_nUID, 0x44)
            CD2_OFFSET(cSpawnPointBase, m_nStatusBitfield, 0x48)
            CD2_OFFSET(cSpawnPointBase, m_bPersistingObject, 0x49))
    };
}

#endif // ACTIVITY_CSPAWNPOINTBASE_H
