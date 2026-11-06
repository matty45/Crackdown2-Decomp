#include "gom/object_prototype.h"
// Hierarchy correction: CD2 debug subobject at 0x120, cBody size 0x250.
#include "rws/attributes.h"
// PHYSICS::cBody (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82683318) builds cClass(0x63C, "cBody", 0x250); 0x250 is the size its registrar gives.
#ifndef PHYSICS_CBODY_H
#define PHYSICS_CBODY_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "GDb/cDebugPageHandler.h"
#include "PHYSICS/cCollisionListener.h"

namespace PHYSICS
{
    class cPhysicsWorld;

    class cBody : public cGameBase, public GDb::cDebugPageHandler
    {
    public:
        // Name and base from RuffKing. CD2's MakeNew (0x82683298) allocates 0x1F0 bytes, RuffKing's size; the
        // constructor (0x826845A8) builds RuffKing's m_apResources (0xE0), m_ConstructInfo (0xF0) and
        // m_pCollisionData (0x1E0) at the same offsets. The fields are not modelled.
        class cBodyPrototype : public cGameBase::cGameBasePrototype
        {
        public:
            cBodyPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelledE0[0x1F0 - 0xE0];

            CD2_LAYOUT_CHECKS(cBodyPrototype,
                CD2_SIZE(cBodyPrototype, 0x1F0))
        };

        // CD2 0x826832F0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FDF730 names placement factory 0x82683300.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual ~cBody();
        // Primary slot 6 (0x826836F8): calls cGameBase's and returns Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);
        virtual Fun_Runtime::RetVal Term();
        virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);
        virtual Fun_Runtime::RetVal TermForReuse();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // Primary slots 141..226: cBody's own virtuals. CD2's cBody table (0x8200C938, stored by the constructor
        // 0x82683400) has 227 slots. Names are not recovered yet; vfN is the slot index.
        virtual void vf141(); virtual void vf142(); virtual void vf143(); virtual void vf144(); virtual void vf145(); virtual void vf146();
        virtual void vf147(); virtual void vf148(); virtual void vf149(); virtual void vf150(); virtual void vf151(); virtual void vf152();
        virtual void vf153(); virtual void vf154(); virtual void vf155(); virtual void vf156(); virtual void vf157(); virtual void vf158();
        virtual void vf159(); virtual void vf160(); virtual void vf161(); virtual void vf162(); virtual void vf163(); virtual void vf164();
        virtual void vf165(); virtual void vf166(); virtual void vf167(); virtual void vf168(); virtual void vf169(); virtual void vf170();
        virtual void vf171(); virtual void vf172(); virtual void vf173(); virtual void vf174(); virtual void vf175(); virtual void vf176();
        virtual void vf177(); virtual void vf178(); virtual void vf179(); virtual void vf180(); virtual void vf181(); virtual void vf182();
        virtual void vf183(); virtual void vf184(); virtual void vf185(); virtual void vf186(); virtual void vf187(); virtual void vf188();
        virtual void vf189(); virtual void vf190(); virtual void vf191(); virtual void vf192(); virtual void vf193(); virtual void vf194();
        virtual void vf195(); virtual void vf196(); virtual unsigned short RetCollisionSystemGroup(); virtual void vf198(); virtual void vf199(); virtual void vf200();
        virtual void vf201(); virtual void vf202(); virtual void vf203(); virtual void vf204(); virtual void vf205(); virtual void vf206();
        virtual void vf207(); virtual void vf208(); virtual void vf209(); virtual void vf210(); virtual void vf211(); virtual void vf212();
        virtual void vf213(); virtual void vf214(); virtual void vf215(); virtual void vf216(); virtual void vf217(); virtual void vf218();
        virtual void vf219(); virtual void vf220(); virtual void vf221(); virtual void vf222(); virtual void vf223(); virtual void vf224();
        virtual void vf225(); virtual void vf226();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // RuffKing names; CD2 offsets from Init (0x82683680), Reinitialise (0x82683780) and the constructor.
        float m_fSpeed;                             // 0x124
        float m_fLastSpeed;                         // 0x128
        unsigned char m_unknown12C[0x220 - 0x12C];  // RuffKing's m_ConstructInfo is at 0x130 (copied by slot 13)
        cPhysicsWorld *m_pMyWorld;                  // 0x220
        hkRigidBody *m_pRigidBody;                  // 0x224
        unsigned char m_unknown228[0x240 - 0x228];  // RuffKing's m_LastMaterial and m_LastHitMaterial
        // RuffKing's last members, at the offsets CD2's constructor (0x82683400) initializes.
        cCollisionListener m_CollisionListener;     // 0x240
        bool m_bSleeping;                           // 0x24C
        bool m_bSuspended;                          // 0x24D, cleared by TermForReuse (0x82683738)
        unsigned char m_nActivationType;            // 0x24E
        bool m_bHasBeenNearLocalPlayer;             // 0x24F
        CD2_LAYOUT_CHECKS(cBody,
            CD2_SIZE(cBody, 0x250)
            CD2_OFFSET(cBody, m_fSpeed, 0x124)
            CD2_OFFSET(cBody, m_pMyWorld, 0x220)
            CD2_OFFSET(cBody, m_CollisionListener, 0x240)
            CD2_OFFSET(cBody, m_bSuspended, 0x24D))
    };
}

#endif // PHYSICS_CBODY_H
