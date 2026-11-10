// PHYSICS::cOnlineOrb (Crackdown 2): STAND-IN. RuffKing: base cPickupBase and the fields below (0x140-0x159 there, 0x150-0x169
// here). CD2's MakeNew (0x827109E0) allocates the registrar's 0x170 bytes, calls cPickupBase's constructor (0x827093D8),
// stores this class's vtables, zeroes m_vBobOffset and m_nCurrentNumPlayers and sets the pickup type to 10. Its deleting
// destructor (0x82710A98) restores the vtables and calls cPickupBase's destructor: an inline empty destructor.
#ifndef PHYSICS_cOnlineOrb_H
#define PHYSICS_cOnlineOrb_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "fun_runtime/vec3.h"
#include "PHYSICS/cPickupBase.h"
#include "cd2/layout.h"

namespace PHYSICS
{
    class cOnlineOrb : public cPickupBase
    {
    public:
        // __forceinline: CD2's MakeNew inlines this constructor; /Ob1 declines a plain inline constructor with this many
        // stores (docs/matching-notes.md, Inlining).
        __forceinline cOnlineOrb() : m_nCurrentNumPlayers(0) { m_ePickupType = 10; }
        virtual ~cOnlineOrb() {}
        static const Fun_Runtime::cClass *ms_pcOnlineOrbClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        Fun_Runtime::Vec3 m_vBobOffset;
        float m_fRequiredPlayerDistance;
        float m_fBobTimer;
        unsigned char m_nNumPlayersToCollect;
        unsigned char m_nCurrentNumPlayers;

        // CD2: cOnlineOrb's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82710BC0
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x82710D28
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cRegisteredClass 1: 0x822E2438
    protected:
        CD2_LAYOUT_CHECKS(cOnlineOrb,
            CD2_SIZE(cOnlineOrb, 0x170)
            CD2_OFFSET(cOnlineOrb, m_vBobOffset, 0x150)
            CD2_OFFSET(cOnlineOrb, m_fRequiredPlayerDistance, 0x160)
            CD2_OFFSET(cOnlineOrb, m_fBobTimer, 0x164)
            CD2_OFFSET(cOnlineOrb, m_nNumPlayersToCollect, 0x168)
            CD2_OFFSET(cOnlineOrb, m_nCurrentNumPlayers, 0x169))
    };
}

#endif
