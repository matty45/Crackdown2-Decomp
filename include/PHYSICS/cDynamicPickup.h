// STAND-IN. Reference cPickup.h gives cPickup and cReplicatedClass as the bases. CD2 constructor 0x8270ACC8 calls
// cPickup first and constructs replication at +0x150 (0x230 bytes). Descriptor 0x8270A670 registers cDynamicPickup
// with size 0x3B0. Its fields are RuffKing's, 0x10 above RuffKing's offsets (as its replication base is 0x10 larger):
// CanPickupNow (0x827092E8) tests the timer at +0x394 where RuffKing's (0x82812018) tests +0x384.
#pragma once
#include "PHYSICS/cPickup.h"
#include "network/cReplicatedClass.h"
#include "fun_runtime/vec3.h"
namespace Fun_Runtime { template <class T> class cQNode; }
namespace GameManagement { class cNetGamePickupSpawnPoint; }
namespace PHYSICS
{
    class cDynamicPickup : public cPickup, public cReplicatedClass
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 initializer 0x82FF0728 stores this pointer at 0x83849534.
        static const Fun_Runtime::cClass *ms_pcDynamicPickupClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2's table 0x82139748 holds its own bodies in slots 6 (0x8270AEA8) and 69 (0x827092E8).
        virtual Fun_Runtime::RetVal Term();
        // RuffKing's inline; CD2's out-of-line copy is 0x827092E8, in this object's text.
        virtual bool CanPickupNow();

    protected:
        Fun_Runtime::Vec3 m_vVelocity;
        bool m_bMotionActive;
        float m_fCantPickupTimer;
        Fun_Runtime::cQNode<cDynamicPickup> *m_pNode;
        GameManagement::cNetGamePickupSpawnPoint *m_pSpawnPoint;

        // CD2's last 0x10 bytes (0x3A0..0x3B0) are not accounted for: RuffKing's class ends with m_pSpawnPoint.
        CD2_LAYOUT_CHECKS(cDynamicPickup,
            CD2_OFFSET(cDynamicPickup, m_vVelocity, 0x380)
            CD2_OFFSET(cDynamicPickup, m_fCantPickupTimer, 0x394)
            CD2_OFFSET(cDynamicPickup, m_pSpawnPoint, 0x39C))
    };
}
