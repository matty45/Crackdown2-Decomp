// VFX::cBeamManager (Crackdown 2): STAND-IN for the registered-class interface only. RuffKing (cBeam.h) derives it
// from GDb::cDebugPageHandler with inline RetClass/IsA; CD2 keeps RetClass (0x82802398) and IsA (0x828023A8) in
// cBeam.obj's range as slots 0/1 of table 0x82155350, reading the class pointer at 0x838FF844 (initializer
// 0x8300BAE0). No instance layout is modelled yet.
#ifndef VFX_CBEAMMANAGER_H
#define VFX_CBEAMMANAGER_H

#include "fun_runtime/class.h"
#include "GDb/cDebugPageHandler.h"

namespace VFX
{
    class cBeamManager : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBeamManagerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
    };
}

#endif // VFX_CBEAMMANAGER_H
