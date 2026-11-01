// AI::cAIAnimEventProfile (Crackdown 2): STAND-IN for the class name only. Base RWS::CAttributeHandler, as in
// RuffKing's header; RetClassName (0x8243D2E8) is slot 11 of the vtable at 0x820FF0D4, as cNonGameBase's RetClassName.
#ifndef AI_CAIANIMEVENTPROFILE_H
#define AI_CAIANIMEVENTPROFILE_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cAIAnimEventProfile : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAIAnimEventProfileClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_CAIANIMEVENTPROFILE_H
