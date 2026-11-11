// CD2 constructor 0x824CCBE8 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#ifndef AI_CAMBIENTTRAFFICBEHAVIOUR_H
#define AI_CAMBIENTTRAFFICBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cAmbientTrafficBehaviour : public AI::NPCBehaviour
    {
    public:
        // CD2 spawning initializer 0x82F99950 names placement factory 0x824ccab8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAmbientTrafficBehaviourClass;

        cAmbientTrafficBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8200B758 differs from NPCBehaviour at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x8222D910
        virtual void OnExit(); // slot 69: 0x824CD380
        virtual void Slot71(); // slot 71: 0x82370AD0
        virtual void Slot79(); // slot 79: 0x824CD338
    };
}

#endif

