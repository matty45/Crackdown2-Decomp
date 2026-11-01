// AudioLogic::cAudioBaseProfile (Crackdown 2): STAND-IN for the class name only. Base RWS::CAttributeHandler, as in
// RuffKing's header; RetClassName (0x825277B8) is slot 11 of the vtable at 0x82111430, as cNonGameBase's RetClassName.
#ifndef AUDIOLOGIC_CAUDIOBASEPROFILE_H
#define AUDIOLOGIC_CAUDIOBASEPROFILE_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AudioLogic
{
    class cAudioBaseProfile : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAudioBaseProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AUDIOLOGIC_CAUDIOBASEPROFILE_H
