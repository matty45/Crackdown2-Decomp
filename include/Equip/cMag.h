// CD2 constructor 0x8260BD28 confirms the shared base constructor chain.
#include "Equip/cCWSatchelCharge.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cMag (Crackdown 2): STAND-IN: constructor-confirmed base and fields. The constructor (0x8260BD28) initializes
// RuffKing's fields in RuffKing's order, 0xA0 below RuffKing's offsets (its base is that much larger), and two more
// bytes RuffKing lacks.
// StaticCreateClass (0x8260BC88) builds cClass(0x27411, "cMag", 0xB20); 0xB20 is the size its registrar gives.
#ifndef EQUIP_CMAG_H
#define EQUIP_CMAG_H

#include "fun_runtime/class.h"
#include "fun_runtime/safedeletablepointer.h"

namespace VFX { class cParticleEffectInstance; }

namespace Equip
{
    class cMag : public Equip::cCWSatchelCharge
    {
    public:
        // RuffKing prototype name/base; CD2 Init is primary slot 5 (0x8260BC78).
        // Interface only: instance fields and allocation size remain unrecovered.
        class cMagPrototype : public cCWSatchelCharge::cCWSatchelChargePrototype
        {
        public:
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        };

        // CD2 factory 0x8260BC60 forwards only this, without a prototype argument.
        cMag();
        // CD2 0x8260BC50: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8260BB10 / 0x8260BB20: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 spawning initializer 0x82FCCC00 names placement factory 0x8260bc60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMagClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // RuffKing override; CD2 primary slot 406 forwards to cExplosiveGrenade::Launched.
        virtual void Launched(cGameBase *pAttacker); // 0x8260D1A8

        // The other slots where CD2's table (0x82120718, stored by the constructor) differs from cCWSatchelCharge's;
        // RuffKing's cMag overrides the named ones too. 427 holds the shared "return 1" body (folded).
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8260BED8
        virtual void TickUpdate(float fDeltaTime); // 23: 0x8260C3B8
        virtual void UpdateRenderMatrix(); // 26: 0x8260DA18
        virtual void vf158(); // 158: 0x8260D498
        virtual void NotifyTracked(cEquipment *pLastTracked); // 342: 0x8260CEF0
        virtual unsigned char RetExplosiveLevelForOwner(const cNonGameBase *) const; // 427: 0x8288FB78
        virtual void NowStuck(); // 432: 0x8260D118
        virtual void Unstick(); // 433: 0x8260D160
        virtual void OnAttachedToObject(cSatchelChargeTarget *pTarget, const Fun_Runtime::Mtx &matOffset); // 434: 0x8260D1B0
        virtual void OnDetachedFromObject(); // 435: 0x8260D348
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8260D528
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x8260D580
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288EE10

    private:
        Fun_Runtime::cSafeDeletablePointer<cMag> m_pNextLink;                 // 0xAE0
        Fun_Runtime::cSafeDeletablePointer<cMag> m_pPrevLink;                 // 0xAF0
        unsigned int m_nReplicatedNextLinkID;                               // 0xB00
        unsigned int m_nReplicatedPrevLinkID;                               // 0xB04
        VFX::cParticleEffectInstance *m_pActiveMagVFX;                      // 0xB08
        VFX::cParticleEffectInstance *m_pBeamMagVFX;                        // 0xB0C
        // Not in RuffKing; the constructor clears both. Names ours.
        bool m_bUnknownB10;
        bool m_bUnknownB11;

        CD2_LAYOUT_CHECKS(cMag,
            CD2_SIZE(cMag, 0xB20)
            CD2_OFFSET(cMag, m_pNextLink, 0xAE0)
            CD2_OFFSET(cMag, m_nReplicatedNextLinkID, 0xB00)
            CD2_OFFSET(cMag, m_pBeamMagVFX, 0xB0C)
            CD2_OFFSET(cMag, m_bUnknownB11, 0xB11))
    };
}

#endif // EQUIP_CMAG_H
