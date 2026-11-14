// STAND-IN: interface only, not an allocation layout. CD2 constructor 0x826779A8
// installs cScriptHost's primary and registered-class tables at +0/+0x14.
// Table 0x8212E9BC slot 0 points to RetClass (0x82676DB8); the descriptor
// initializer 0x82FDD270 calls cGangInfo's descriptor factory at 0x82677910.
// The class name comes from that descriptor and RuffKing's GangManager/cGangInfo.h.
#ifndef GANGMANAGER_CGANGINFO_H
#define GANGMANAGER_CGANGINFO_H
#include "fun_runtime/scripthost.h"
namespace GangManager
{
    class cGangInfo : public Fun_Runtime::cScriptHost
    {
    public:
        // CD2's 104-byte deleting wrapper restores both tables before cScriptHost cleanup.
        virtual ~cGangInfo() {}
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcGangInfoClass;
    };
}
#endif
