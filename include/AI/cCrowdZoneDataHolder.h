// AI::cCrowdZoneDataHolder (Crackdown 2): STAND-IN. Evidence: MakeNew (0x8244A770) allocates 0x7C bytes (the size its
// registrar gives), calls cNonGameBase's constructor (0x82653588) and installs the five vtables of a cNonGameBase
// (at 0, 0x18, 0x1C, 0x30, 0x38): a cNonGameBase with no fields of its own.
#ifndef AI_cCrowdZoneDataHolder_H
#define AI_cCrowdZoneDataHolder_H

#include "gom/non_game_base.h"

namespace AI
{
    class cCrowdZoneDataHolder : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 registered-class vtable 0x82100D30 slot 0, descriptor at 0x8381A9C8.
        static const Fun_Runtime::cClass *ms_pcCrowdZoneDataHolderClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
