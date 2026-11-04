#ifndef CHARACTER_cRagdollProfile_H
#define CHARACTER_cRagdollProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace CHARACTER
{
    class cRagdollProfile : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcRagdollProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82577D68 (MakeNew calls it).
        cRagdollProfile();

    private:
        unsigned char m_unmodelled18[0x3B0 - 0x18];

        CD2_LAYOUT_CHECKS(cRagdollProfile, CD2_SIZE(cRagdollProfile, 0x3B0))

    };
}

#endif
