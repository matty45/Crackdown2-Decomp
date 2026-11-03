// STAND-IN: CD2 release interface: three slots, as cRopes and table 0x8213FDA4.
#ifndef CD2_GDB_CDEBUGPAGEHANDLER_H
#define CD2_GDB_CDEBUGPAGEHANDLER_H
#include "fun_runtime/class.h"
namespace GDb
{
    class cDebugPageHandler : public Fun_Runtime::cRegisteredClass
    {
    public:
        // CD2 0x82679238 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        cDebugPageHandler() {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual ~cDebugPageHandler() {}
    };
}
#endif
