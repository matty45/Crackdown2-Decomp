#include "fun_runtime/class.h"
// STAND-IN: RuffKing hierarchy; CD2 subobjects at 0, 0x420 and 0x510; cProp interfaces start at 0x7A0.
#ifndef CD2_PHYSICS_CNETDYNAMICBODY_H
#define CD2_PHYSICS_CNETDYNAMICBODY_H
#include "PHYSICS/cDynamicBody.h"
#include "Network/cPositionalProxy.h"
#include "Network/cReplicatedClass.h"
namespace PHYSICS
{
    class cNetDynamicBody : public cDynamicBody, public cPositionalProxy, public cReplicatedClass
    {
    public:
        // CD2 initializer 0x82FDFC60 calls this class's descriptor factory.
        static const Fun_Runtime::cClass *ms_pcNetDynamicBodyClass;
        // CD2 0x82687E38 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual ~cNetDynamicBody();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual bool IsSequential() const;
        virtual bool IsOwnedLocally();
        virtual void SetPingedFieldStatesForNode(unsigned char);
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
    private:
        unsigned char m_unknown740[0x7A0 - 0x740];
        CD2_LAYOUT_CHECKS(cNetDynamicBody, CD2_SIZE(cNetDynamicBody, 0x7A0))
    };
}
#endif
