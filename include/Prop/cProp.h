// Prop::cProp and Prop::cProp::cPropPrototype (Crackdown 2): STAND-INS, sized to CD2. Only what derived props need so
// far. Evidence:
// - cProp is 0xE30 bytes: its registrar (0x82FF5298) registers the class with size 0xE30, and cTrafficLight's first own
//   field (a long long) sits at 0xE30 (cTrafficLight's constructor, 0x82747470).
// - Bases: RuffKing's cProp derives from PHYSICS::cNetDynamicBody (CD2 registers it with size 0x7A0, 0x82687E38),
//   ExplosionManager::cExplosionCallback, AI::cDynamicObstacleOwner and Equip::cSatchelChargeTarget. None of them is in
//   the repo yet, so this stand-in derives straight from cNonGameBase (gom/non_game_base.h; the chain reaches it
//   through cGameBase and PHYSICS::cBody) and pads up to 0xE30. The secondary bases are not modelled.
// - UpdateRenderMatrix is primary vtable slot 26. cProp's vtable (0x8200DFC8) holds 0x826DA5B8 there; that function
//   first calls 0x82683DC0, slot 26 of PHYSICS::cBody's vtable, which copies the body matrix into the frame's render
//   matrix buffer, then updates the objects attached to the body. RuffKing's cProp overrides UpdateRenderMatrix
//   (protected), as does cTrafficLight. 0x826DA5B8 lies in cVehicle's code and the vehicle vtables use it too: cProp's
//   override and cVehicle's are byte-identical and the linker folded them (ICF), so the name here is cProp's.
// - cPropPrototype is 0x4F0 bytes: cProp's MakeNew (0x82729378) allocates 0x4F0 bytes and calls the constructor
//   0x8272D390 with the packet; cTrafficLight's prototype (0x510 bytes) calls the same constructor.
#ifndef PROP_CPROP_H
#define PROP_CPROP_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "gom/non_game_base.h"
#include "gom/object_prototype.h"

namespace Prop
{
    class cProp : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        class cPropPrototype : public GOM::cObjectPrototype
        {
        private:
            unsigned char m_pad70[0x4F0 - 0x70];

        public:
            cPropPrototype(const RWS::CAttributePacket &);   // 0x8272D390

            CD2_LAYOUT_CHECKS(cPropPrototype,
                CD2_SIZE(cPropPrototype, 0x4F0))
        };

    private:
        unsigned char m_pad7C[0xE30 - 0x7C];

    protected:
        virtual void UpdateRenderMatrix();   // overrides cNonGameBase's slot 26; 0x826DA5B8 (folded with cVehicle's)

        CD2_LAYOUT_CHECKS(cProp,
            CD2_SIZE(cProp, 0xE30))
    };
}

#endif // PROP_CPROP_H
