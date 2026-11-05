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
    };
}

#endif