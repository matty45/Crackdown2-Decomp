#include "gom/object_prototype.h"
#ifndef Prop_cPintleFaceplate_H
#define Prop_cPintleFaceplate_H

#include "Prop/cProp.h"
#include "fun_runtime/class.h"

namespace Prop
{
    // STAND-IN: CD2 0x827453D8 invokes cProp's destructor; derived storage is not modelled yet.
    class cPintleFaceplate : public cProp
    {
    public:
        // CD2 spawning initializer 0x82FFB720 names placement factory 0x82745208.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual ~cPintleFaceplate();
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcPintleFaceplateClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // CD2: cPintleFaceplate's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual bool EnterPhysicalState(); // 7: 0x82745578
        virtual void Slot23(); // 23: 0x822C2DF0
        virtual void vf271(); // 271: 0x82745490
        virtual void vf272(); // 272: 0x827454F8
    };
}

#endif
