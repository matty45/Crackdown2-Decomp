#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
// AI::AIBehaviour (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's header;
// RetClassName (0x824A4A80) is slot 11 of the vtable at 0x82107B90, as cNonGameBase's RetClassName.
#ifndef AI_AIBEHAVIOUR_H
#define AI_AIBEHAVIOUR_H

#include "gom/non_game_base.h"

namespace AI
{
    class AIBehaviour : public cNonGameBase
    {
    public:
        // CD2 table 0x82107B90 has 72 entries. Slots 68..71 are shared by NPC behaviours.
        virtual void OnEnter();
        virtual void OnExit();
        virtual void Slot70();
        virtual void Slot71();

        static const Fun_Runtime::cClass *ms_pAIBehaviourClass;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 MakeNew (0x824a4a10) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class AIBehaviourPrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline AIBehaviourPrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}
            // CD2's table 0x82107B60 has twelve slots; RuffKing names the
            // prototype's sole additional virtual RetPrimaryWeapon.
            virtual const RWS::RWSGUID &RetPrimaryWeapon() const;

            CD2_LAYOUT_CHECKS(AIBehaviourPrototype, CD2_SIZE(AIBehaviourPrototype, 0x70))
        };

        // CD2 0x824A4B18 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2: AIBehaviour's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x827FBD60
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
        virtual Fun_Runtime::cClass const & RetClass() const; // cRegisteredClass 0: 0x824A8720
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cRegisteredClass 1: 0x824A8730
    };
}

#endif // AI_AIBEHAVIOUR_H
