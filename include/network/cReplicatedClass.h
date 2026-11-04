// STAND-IN: RuffKing 24-slot order/size; CD2 table 0x8213FDF0, destructor slot 7.
#ifndef CD2_NETWORK_CREPLICATEDCLASS_H
#define CD2_NETWORK_CREPLICATEDCLASS_H
#include "fun_runtime/class.h"
#include "Network/SNetworkHeader.h"
enum etGameMessageType { };
// CD2 cMissionBase places this base at +0x10 after a four-byte registered-class base.
// The reference starts its first field at +0x10 and its bit stream at +0x20.
__declspec(align(16)) class cReplicatedClass
{
public:
    virtual const Fun_Runtime::cClass &RetClass() const;
    virtual bool IsA(const Fun_Runtime::cClass &) const;
    virtual void CalculateRelevancy(int);
    virtual void CalculateLOD(int);
    virtual bool CanSendTermPacketOnNotRelevant() const;
    virtual bool IsInLODRange(unsigned char);
    virtual bool IsSequential() const = 0;
    virtual ~cReplicatedClass();
    virtual void ReplicateInitialFields();
    virtual void ReplicateFields();
    virtual void ReplicateHeaderData();
    virtual void SkipDefaultReplicatedFields();
    virtual void ReplicateFieldsRead();
    virtual void ReplicateFieldsWrite();
    virtual bool IsOwnedLocally() = 0;
    virtual void SendNetInitRequestMsg();
    virtual unsigned int GetNumObjectIDBits() const;
    virtual unsigned int GetOwnerShipTimeStamp();
    virtual etGameMessageType GetTermMessageType() const;
    virtual void SetReplicatedObjectID(unsigned int);
    virtual void SetPingedFieldStatesForNode(unsigned char) = 0;
    virtual void SetOwnerShipTimeStamp(unsigned int);
    virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const = 0;
    virtual unsigned int GetMaxReplicatedFields() const = 0;
private:
    unsigned char m_unknown4[0x230 - 4];
    CD2_LAYOUT_CHECKS(cReplicatedClass, CD2_SIZE(cReplicatedClass, 0x230))
};
#endif
