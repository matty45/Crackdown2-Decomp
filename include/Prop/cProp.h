// Hierarchy correction: the CD2 interfaces at 0x120, 0x250, 0x294, 0x420,
// 0x510, 0x7A0, 0x7A4 and 0x7AC are now modelled; the historical direct-base
// stand-in described below is superseded.
// Prop::cProp and Prop::cProp::cPropPrototype (Crackdown 2): STAND-INS, sized to CD2. Only what derived props need so
// far. Evidence:
// - cProp is 0xE30 bytes: its registrar (0x82FF5298) registers the class with size 0xE30, and cTrafficLight's first own
//   field (a long long) sits at 0xE30 (cTrafficLight's constructor, 0x82747470).
// - Bases: PHYSICS::cNetDynamicBody (CD2 size 0x7A0, descriptor 0x82687E38), ExplosionManager::cExplosionCallback,
//   AI::cDynamicObstacleOwner and Equip::cSatchelChargeTarget follow the reference order. CD2's constructor
//   0x82337808 confirms their subobjects and the 341-slot primary interface; only cProp's own fields remain opaque.
// - UpdateRenderMatrix is primary vtable slot 26. cProp's vtable (0x8200DFC8) holds 0x826DA5B8 there; that function
//   first calls 0x82683DC0, slot 26 of PHYSICS::cBody's vtable, which copies the body matrix into the frame's render
//   matrix buffer, then updates the objects attached to the body. RuffKing's cProp overrides UpdateRenderMatrix
//   (protected), as does cTrafficLight. 0x826DA5B8 lies in cVehicle's code and the vehicle vtables use it too: cProp's
//   override and cVehicle's are byte-identical and the linker folded them (ICF), so the name here is cProp's.
// - cPropPrototype is 0x4F0 bytes: cProp's MakeNew (0x82729378) allocates 0x4F0 bytes and calls the constructor
//   0x8272D390 with the packet; cTrafficLight's prototype (0x510 bytes) calls the same constructor.
#ifndef PROP_CPROP_H
#define PROP_CPROP_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "ExplosionManager/cExplosionCallback.h"
#include "AI/cDynamicObstacleOwner.h"
#include "Equip/cSatchelChargeTarget.h"
#include "gom/object_prototype.h"

namespace Prop
{
    class cProp : public PHYSICS::cNetDynamicBody, public ExplosionManager::cExplosionCallback,
        public AI::cDynamicObstacleOwner, public Equip::cSatchelChargeTarget
    {
    public:
        // CD2 0x827293E0: placement factory.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x82729410 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPropClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82729538, called by cTrafficLight's destructor (0x827475C8).
        cProp(GOM::cObjectPrototype *); // CD2 0x82337808
        virtual ~cProp();
        virtual Fun_Runtime::RetVal Term(); // CD2 0x822C5828
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *); // CD2 0x827296C0, primary slot 18
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        virtual void CreateDynamicObstacle();
        virtual void ActivateDynamicObstacle();
        virtual unsigned char GetDynamicObstacleInput();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2's cProp table 0x8200DFC8 has 341 primary slots, extending cNetDynamicBody's 314.
        // These slot indices are retained until the individual virtual names/signatures are recovered.
        virtual void vf314(); virtual void vf315(); virtual void vf316(); virtual void vf317(); virtual void vf318();
        virtual void vf319(); virtual void vf320(); virtual void vf321(); virtual void vf322(); virtual void vf323();
        virtual void vf324(); virtual void vf325(); virtual void vf326(); virtual void vf327(); virtual void vf328();
        virtual void vf329(); virtual void vf330(); virtual void vf331(); virtual void vf332(); virtual void vf333();
        virtual void vf334(); virtual void vf335(); virtual void vf336(); virtual void vf337(); virtual void vf338();
        virtual void vf339(); virtual void vf340();
        class cPropPrototype : public GOM::cObjectPrototype
        {
        private:
            unsigned char m_pad70[0x4F0 - 0x70];

        public:
            cPropPrototype(const RWS::CAttributePacket &);   // 0x8272D390
            // CD2 0x8272D688, called by derived prototype attribute handlers.
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cPropPrototype,
                CD2_SIZE(cPropPrototype, 0x4F0))
        };

    private:
        unsigned char m_unknown7B4[0xE30 - 0x7B4];

    protected:
        virtual void UpdateRenderMatrix();   // overrides cNonGameBase's slot 26; 0x826DA5B8 (folded with cVehicle's)

        CD2_LAYOUT_CHECKS(cProp,
            CD2_SIZE(cProp, 0xE30))
    };
}

#endif // PROP_CPROP_H
