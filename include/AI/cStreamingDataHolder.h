#ifndef AI_CSTREAMINGDATAHOLDER_H
#define AI_CSTREAMINGDATAHOLDER_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cStreamingDataHolder : public cNonGameBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcStreamingDataHolderClass;

        cStreamingDataHolder();
        // CD2's deleting destructor 0x8244C1A8 restores the five cNonGameBase vptrs before calling ~cNonGameBase: a
        // user-declared empty destructor, inlined there (docs/matching-notes.md, Destructors).
        virtual ~cStreamingDataHolder() {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);
        // CD2: cStreamingDataHolder's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8244C238
        virtual int RetUniqueID(); // CEventHandler 1: 0x82604E70
    };
}

#endif