// CD2 constructor 0x827570B0 confirms the shared base constructor chain.
#include "PHYSICS/cBody.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "Audio/cPickupGameObject.h"
// RPG::cRenegadeOrb (Crackdown 2): STAND-IN: constructor-confirmed base; the first two members are RuffKing's, the
// remaining instance fields are not modelled. StaticCreateClass (0x82757018) builds cClass(0x67B, "cRenegadeOrb",
// 0x3B0); 0x3B0 is the size its registrar gives. The constructor (0x827570B0) clears the effect pointer at 0x250 (the
// end of cBody) and expands the audio object's constructor at 0x258; the destructor (0x82757240) destroys only that
// object before ~cBody.
#ifndef RPG_CRENEGADEORB_H
#define RPG_CRENEGADEORB_H

#include "fun_runtime/class.h"

namespace VFX { class cParticleEffectInstance; }

namespace RPG
{
    class cRenegadeOrb : public PHYSICS::cBody
    {
    public:
        // CD2 factory 0x82757000 forwards only this, without a prototype argument.
        cRenegadeOrb();
        virtual ~cRenegadeOrb();
        virtual bool EnterPhysicalState(); // CD2 table 0x8200CCC8, slot 7
        // CD2 0x82756FF0: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x82756EF0 / 0x82756F00: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 spawning initializer 0x82FFE5C8 names placement factory 0x82757000.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRenegadeOrbClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        // RuffKing's other overrides: CD2's table 0x8200CCC8 holds this class's code for each (Term 0x82757350, Init
        // 0x827572D0, SetSpawner 0x82757610, TickUpdate 0x8220FCD8, Enter/LeaveRenderableState 0x82758130/0x827581C8,
        // TakeDamage 0x82757498); its LeavePhysicalState slot holds cNonGameBase's body (0x82653BC8), which skipping
        // cBody's, as EnterPhysicalState does, folds into.
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *pSpawnArgs);
        virtual Fun_Runtime::RetVal Term();
        virtual void TickUpdate(float dt);
        virtual bool EnterRenderableState(eResourcesType eResources);
        virtual void LeaveRenderableState();
        virtual void SetSpawner(Activity::cSpawnPointBase *pSpawner);
        virtual void LeavePhysicalState();
        virtual float TakeDamage(Damage::cDamage &Damage);
        // RuffKing's inline overrides; CD2's table (0x8200CCC8) holds the shared empty body (0x82580578) in slot 26 and the
        // shared return-true body (0x8288FB78) in slot 15.
        virtual void UpdateRenderMatrix() {}

    protected:
        virtual bool HandleRenderableResources(GOM::cObjectPrototype *) { return true; }

        VFX::cParticleEffectInstance *m_pOrbVFX;
        Audio::cPickupGameObject m_RenegadeOrbAudio;

        CD2_LAYOUT_CHECKS(cRenegadeOrb,
            CD2_OFFSET(cRenegadeOrb, m_pOrbVFX, 0x250)
            CD2_OFFSET(cRenegadeOrb, m_RenegadeOrbAudio, 0x258))
    };
}

#endif // RPG_CRENEGADEORB_H
