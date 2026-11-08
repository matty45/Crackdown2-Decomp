#ifndef Anim_cSkeletonProfile_H
#define Anim_cSkeletonProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "gom/non_game_base.h"

namespace Anim
{
    class cSkeletonProfile : public cNonGameBase
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcSkeletonProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x824E6910 (MakeNew calls it with the packet).
        cSkeletonProfile(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled7C[0x190 - 0x7C];

        CD2_LAYOUT_CHECKS(cSkeletonProfile, CD2_SIZE(cSkeletonProfile, 0x190))

    };
}

#endif
